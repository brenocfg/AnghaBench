#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int u32 ;
struct TYPE_3__ {int* ptr; } ;
struct radeon_cs_parser {scalar_t__ track; TYPE_1__ ib; } ;
struct radeon_cs_packet {int /*<<< orphan*/  opcode; } ;
struct radeon_bo_list {int /*<<< orphan*/  robj; scalar_t__ gpu_offset; } ;
struct r100_cs_track {unsigned int num_arrays; TYPE_2__* arrays; } ;
struct TYPE_4__ {int esize; int /*<<< orphan*/  robj; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  radeon_cs_dump_packet (struct radeon_cs_parser*,struct radeon_cs_packet*) ; 
 int radeon_cs_packet_next_reloc (struct radeon_cs_parser*,struct radeon_bo_list**,int /*<<< orphan*/ ) ; 
 int radeon_get_ib_value (struct radeon_cs_parser*,int) ; 

int r100_packet3_load_vbpntr(struct radeon_cs_parser *p,
			     struct radeon_cs_packet *pkt,
			     int idx)
{
	unsigned c, i;
	struct radeon_bo_list *reloc;
	struct r100_cs_track *track;
	int r = 0;
	volatile uint32_t *ib;
	u32 idx_value;

	ib = p->ib.ptr;
	track = (struct r100_cs_track *)p->track;
	c = radeon_get_ib_value(p, idx++) & 0x1F;
	if (c > 16) {
	    DRM_ERROR("Only 16 vertex buffers are allowed %d\n",
		      pkt->opcode);
	    radeon_cs_dump_packet(p, pkt);
	    return -EINVAL;
	}
	track->num_arrays = c;
	for (i = 0; i < (c - 1); i+=2, idx+=3) {
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		if (r) {
			DRM_ERROR("No reloc for packet3 %d\n",
				  pkt->opcode);
			radeon_cs_dump_packet(p, pkt);
			return r;
		}
		idx_value = radeon_get_ib_value(p, idx);
		ib[idx+1] = radeon_get_ib_value(p, idx + 1) + ((u32)reloc->gpu_offset);

		track->arrays[i + 0].esize = idx_value >> 8;
		track->arrays[i + 0].robj = reloc->robj;
		track->arrays[i + 0].esize &= 0x7F;
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		if (r) {
			DRM_ERROR("No reloc for packet3 %d\n",
				  pkt->opcode);
			radeon_cs_dump_packet(p, pkt);
			return r;
		}
		ib[idx+2] = radeon_get_ib_value(p, idx + 2) + ((u32)reloc->gpu_offset);
		track->arrays[i + 1].robj = reloc->robj;
		track->arrays[i + 1].esize = idx_value >> 24;
		track->arrays[i + 1].esize &= 0x7F;
	}
	if (c & 1) {
		r = radeon_cs_packet_next_reloc(p, &reloc, 0);
		if (r) {
			DRM_ERROR("No reloc for packet3 %d\n",
					  pkt->opcode);
			radeon_cs_dump_packet(p, pkt);
			return r;
		}
		idx_value = radeon_get_ib_value(p, idx);
		ib[idx+1] = radeon_get_ib_value(p, idx + 1) + ((u32)reloc->gpu_offset);
		track->arrays[i + 0].robj = reloc->robj;
		track->arrays[i + 0].esize = idx_value >> 8;
		track->arrays[i + 0].esize &= 0x7F;
	}
	return r;
}