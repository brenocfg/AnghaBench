#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int uint64_t ;
struct TYPE_4__ {unsigned int* ptr; } ;
struct radeon_cs_parser {int idx; TYPE_3__* rdev; TYPE_1__ ib; struct radeon_bo_list* relocs; struct radeon_cs_chunk* chunk_relocs; } ;
struct radeon_cs_chunk {unsigned int length_dw; } ;
struct radeon_bo_list {unsigned int gpu_offset; int /*<<< orphan*/  robj; } ;
struct TYPE_5__ {int gpu_addr; } ;
struct TYPE_6__ {TYPE_2__ uvd; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 unsigned int radeon_bo_size (int /*<<< orphan*/ ) ; 
 int radeon_get_ib_value (struct radeon_cs_parser*,int) ; 
 int radeon_uvd_cs_msg (struct radeon_cs_parser*,int /*<<< orphan*/ ,unsigned int,unsigned int*) ; 

__attribute__((used)) static int radeon_uvd_cs_reloc(struct radeon_cs_parser *p,
			       int data0, int data1,
			       unsigned buf_sizes[], bool *has_msg_cmd)
{
	struct radeon_cs_chunk *relocs_chunk;
	struct radeon_bo_list *reloc;
	unsigned idx, cmd, offset;
	uint64_t start, end;
	int r;

	relocs_chunk = p->chunk_relocs;
	offset = radeon_get_ib_value(p, data0);
	idx = radeon_get_ib_value(p, data1);
	if (idx >= relocs_chunk->length_dw) {
		DRM_ERROR("Relocs at %d after relocations chunk end %d !\n",
			  idx, relocs_chunk->length_dw);
		return -EINVAL;
	}

	reloc = &p->relocs[(idx / 4)];
	start = reloc->gpu_offset;
	end = start + radeon_bo_size(reloc->robj);
	start += offset;

	p->ib.ptr[data0] = start & 0xFFFFFFFF;
	p->ib.ptr[data1] = start >> 32;

	cmd = radeon_get_ib_value(p, p->idx) >> 1;

	if (cmd < 0x4) {
		if (end <= start) {
			DRM_ERROR("invalid reloc offset %X!\n", offset);
			return -EINVAL;
		}
		if ((end - start) < buf_sizes[cmd]) {
			DRM_ERROR("buffer (%d) to small (%d / %d)!\n", cmd,
				  (unsigned)(end - start), buf_sizes[cmd]);
			return -EINVAL;
		}

	} else if (cmd != 0x100) {
		DRM_ERROR("invalid UVD command %X!\n", cmd);
		return -EINVAL;
	}

	if ((start >> 28) != ((end - 1) >> 28)) {
		DRM_ERROR("reloc %LX-%LX crossing 256MB boundary!\n",
			  start, end);
		return -EINVAL;
	}

	/* TODO: is this still necessary on NI+ ? */
	if ((cmd == 0 || cmd == 0x3) &&
	    (start >> 28) != (p->rdev->uvd.gpu_addr >> 28)) {
		DRM_ERROR("msg/fb buffer %LX-%LX out of 256MB segment!\n",
			  start, end);
		return -EINVAL;
	}

	if (cmd == 0) {
		if (*has_msg_cmd) {
			DRM_ERROR("More than one message in a UVD-IB!\n");
			return -EINVAL;
		}
		*has_msg_cmd = true;
		r = radeon_uvd_cs_msg(p, reloc->robj, offset, buf_sizes);
		if (r)
			return r;
	} else if (!*has_msg_cmd) {
		DRM_ERROR("Message needed before other commands are send!\n");
		return -EINVAL;
	}

	return 0;
}