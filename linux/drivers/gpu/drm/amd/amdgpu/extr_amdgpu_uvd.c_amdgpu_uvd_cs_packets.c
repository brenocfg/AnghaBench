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
typedef  int /*<<< orphan*/  uint32_t ;
struct amdgpu_uvd_cs_ctx {size_t ib_idx; scalar_t__ idx; int /*<<< orphan*/  count; int /*<<< orphan*/  reg; TYPE_2__* parser; } ;
struct amdgpu_ib {scalar_t__ length_dw; } ;
struct TYPE_4__ {TYPE_1__* job; } ;
struct TYPE_3__ {struct amdgpu_ib* ibs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CP_PACKET0_GET_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CP_PACKET_GET_COUNT (int /*<<< orphan*/ ) ; 
 unsigned int CP_PACKET_GET_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,unsigned int) ; 
 int EINVAL ; 
#define  PACKET_TYPE0 129 
#define  PACKET_TYPE2 128 
 int /*<<< orphan*/  amdgpu_get_ib_value (TYPE_2__*,size_t,scalar_t__) ; 
 int amdgpu_uvd_cs_reg (struct amdgpu_uvd_cs_ctx*,int (*) (struct amdgpu_uvd_cs_ctx*)) ; 

__attribute__((used)) static int amdgpu_uvd_cs_packets(struct amdgpu_uvd_cs_ctx *ctx,
				 int (*cb)(struct amdgpu_uvd_cs_ctx *ctx))
{
	struct amdgpu_ib *ib = &ctx->parser->job->ibs[ctx->ib_idx];
	int r;

	for (ctx->idx = 0 ; ctx->idx < ib->length_dw; ) {
		uint32_t cmd = amdgpu_get_ib_value(ctx->parser, ctx->ib_idx, ctx->idx);
		unsigned type = CP_PACKET_GET_TYPE(cmd);
		switch (type) {
		case PACKET_TYPE0:
			ctx->reg = CP_PACKET0_GET_REG(cmd);
			ctx->count = CP_PACKET_GET_COUNT(cmd);
			r = amdgpu_uvd_cs_reg(ctx, cb);
			if (r)
				return r;
			break;
		case PACKET_TYPE2:
			++ctx->idx;
			break;
		default:
			DRM_ERROR("Unknown packet type %d !\n", type);
			return -EINVAL;
		}
	}
	return 0;
}