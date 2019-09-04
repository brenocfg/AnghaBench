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
struct amdgpu_uvd_cs_ctx {size_t ib_idx; scalar_t__ idx; int count; int reg; scalar_t__ data0; scalar_t__ data1; TYPE_2__* parser; } ;
struct amdgpu_ib {scalar_t__ length_dw; } ;
struct TYPE_4__ {TYPE_1__* job; } ;
struct TYPE_3__ {struct amdgpu_ib* ibs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
#define  mmUVD_ENGINE_CNTL 132 
#define  mmUVD_GPCOM_VCPU_CMD 131 
#define  mmUVD_GPCOM_VCPU_DATA0 130 
#define  mmUVD_GPCOM_VCPU_DATA1 129 
#define  mmUVD_NO_OP 128 

__attribute__((used)) static int amdgpu_uvd_cs_reg(struct amdgpu_uvd_cs_ctx *ctx,
			     int (*cb)(struct amdgpu_uvd_cs_ctx *ctx))
{
	struct amdgpu_ib *ib = &ctx->parser->job->ibs[ctx->ib_idx];
	int i, r;

	ctx->idx++;
	for (i = 0; i <= ctx->count; ++i) {
		unsigned reg = ctx->reg + i;

		if (ctx->idx >= ib->length_dw) {
			DRM_ERROR("Register command after end of CS!\n");
			return -EINVAL;
		}

		switch (reg) {
		case mmUVD_GPCOM_VCPU_DATA0:
			ctx->data0 = ctx->idx;
			break;
		case mmUVD_GPCOM_VCPU_DATA1:
			ctx->data1 = ctx->idx;
			break;
		case mmUVD_GPCOM_VCPU_CMD:
			r = cb(ctx);
			if (r)
				return r;
			break;
		case mmUVD_ENGINE_CNTL:
		case mmUVD_NO_OP:
			break;
		default:
			DRM_ERROR("Invalid reg 0x%X!\n", reg);
			return -EINVAL;
		}
		ctx->idx++;
	}
	return 0;
}