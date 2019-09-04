#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int uint32_t ;
struct amdgpu_uvd_cs_ctx {scalar_t__* buf_sizes; int has_msg_cmd; TYPE_4__* parser; int /*<<< orphan*/  idx; int /*<<< orphan*/  ib_idx; int /*<<< orphan*/  data1; int /*<<< orphan*/  data0; } ;
struct amdgpu_bo_va_mapping {scalar_t__ last; scalar_t__ start; } ;
struct amdgpu_bo {int dummy; } ;
struct TYPE_10__ {TYPE_3__* adev; } ;
struct TYPE_8__ {TYPE_1__* inst; int /*<<< orphan*/  address_64_bit; } ;
struct TYPE_9__ {TYPE_2__ uvd; } ;
struct TYPE_7__ {int gpu_addr; } ;

/* Variables and functions */
 scalar_t__ AMDGPU_GPU_PAGE_SIZE ; 
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 scalar_t__ amdgpu_bo_gpu_offset (struct amdgpu_bo*) ; 
 int amdgpu_cs_find_mapping (TYPE_4__*,scalar_t__,struct amdgpu_bo**,struct amdgpu_bo_va_mapping**) ; 
 int amdgpu_get_ib_value (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_set_ib_value (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int amdgpu_uvd_cs_msg (struct amdgpu_uvd_cs_ctx*,struct amdgpu_bo*,scalar_t__) ; 
 scalar_t__ amdgpu_uvd_get_addr_from_ctx (struct amdgpu_uvd_cs_ctx*) ; 
 int /*<<< orphan*/  lower_32_bits (scalar_t__) ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 

__attribute__((used)) static int amdgpu_uvd_cs_pass2(struct amdgpu_uvd_cs_ctx *ctx)
{
	struct amdgpu_bo_va_mapping *mapping;
	struct amdgpu_bo *bo;
	uint32_t cmd;
	uint64_t start, end;
	uint64_t addr = amdgpu_uvd_get_addr_from_ctx(ctx);
	int r;

	r = amdgpu_cs_find_mapping(ctx->parser, addr, &bo, &mapping);
	if (r) {
		DRM_ERROR("Can't find BO for addr 0x%08Lx\n", addr);
		return r;
	}

	start = amdgpu_bo_gpu_offset(bo);

	end = (mapping->last + 1 - mapping->start);
	end = end * AMDGPU_GPU_PAGE_SIZE + start;

	addr -= mapping->start * AMDGPU_GPU_PAGE_SIZE;
	start += addr;

	amdgpu_set_ib_value(ctx->parser, ctx->ib_idx, ctx->data0,
			    lower_32_bits(start));
	amdgpu_set_ib_value(ctx->parser, ctx->ib_idx, ctx->data1,
			    upper_32_bits(start));

	cmd = amdgpu_get_ib_value(ctx->parser, ctx->ib_idx, ctx->idx) >> 1;
	if (cmd < 0x4) {
		if ((end - start) < ctx->buf_sizes[cmd]) {
			DRM_ERROR("buffer (%d) to small (%d / %d)!\n", cmd,
				  (unsigned)(end - start),
				  ctx->buf_sizes[cmd]);
			return -EINVAL;
		}

	} else if (cmd == 0x206) {
		if ((end - start) < ctx->buf_sizes[4]) {
			DRM_ERROR("buffer (%d) to small (%d / %d)!\n", cmd,
					  (unsigned)(end - start),
					  ctx->buf_sizes[4]);
			return -EINVAL;
		}
	} else if ((cmd != 0x100) && (cmd != 0x204)) {
		DRM_ERROR("invalid UVD command %X!\n", cmd);
		return -EINVAL;
	}

	if (!ctx->parser->adev->uvd.address_64_bit) {
		if ((start >> 28) != ((end - 1) >> 28)) {
			DRM_ERROR("reloc %LX-%LX crossing 256MB boundary!\n",
				  start, end);
			return -EINVAL;
		}

		if ((cmd == 0 || cmd == 0x3) &&
		    (start >> 28) != (ctx->parser->adev->uvd.inst->gpu_addr >> 28)) {
			DRM_ERROR("msg/fb buffer %LX-%LX out of 256MB segment!\n",
				  start, end);
			return -EINVAL;
		}
	}

	if (cmd == 0) {
		ctx->has_msg_cmd = true;
		r = amdgpu_uvd_cs_msg(ctx, bo, addr);
		if (r)
			return r;
	} else if (!ctx->has_msg_cmd) {
		DRM_ERROR("Message needed before other commands are send!\n");
		return -EINVAL;
	}

	return 0;
}