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
typedef  size_t uint32_t ;
struct amdgpu_uvd_cs_ctx {unsigned int* buf_sizes; size_t ib_idx; int /*<<< orphan*/  has_msg_cmd; struct amdgpu_cs_parser* parser; } ;
struct amdgpu_ib {int length_dw; int /*<<< orphan*/  sa_bo; int /*<<< orphan*/  gpu_addr; } ;
struct amdgpu_cs_parser {TYPE_3__* adev; TYPE_1__* job; } ;
struct TYPE_5__ {int /*<<< orphan*/  address_64_bit; } ;
struct TYPE_6__ {TYPE_2__ uvd; } ;
struct TYPE_4__ {int /*<<< orphan*/ * vm; struct amdgpu_ib* ibs; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*,...) ; 
 int EINVAL ; 
 int /*<<< orphan*/  amdgpu_sa_bo_gpu_addr (int /*<<< orphan*/ ) ; 
 int amdgpu_uvd_cs_packets (struct amdgpu_uvd_cs_ctx*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  amdgpu_uvd_cs_pass1 ; 
 int /*<<< orphan*/  amdgpu_uvd_cs_pass2 ; 

int amdgpu_uvd_ring_parse_cs(struct amdgpu_cs_parser *parser, uint32_t ib_idx)
{
	struct amdgpu_uvd_cs_ctx ctx = {};
	unsigned buf_sizes[] = {
		[0x00000000]	=	2048,
		[0x00000001]	=	0xFFFFFFFF,
		[0x00000002]	=	0xFFFFFFFF,
		[0x00000003]	=	2048,
		[0x00000004]	=	0xFFFFFFFF,
	};
	struct amdgpu_ib *ib = &parser->job->ibs[ib_idx];
	int r;

	parser->job->vm = NULL;
	ib->gpu_addr = amdgpu_sa_bo_gpu_addr(ib->sa_bo);

	if (ib->length_dw % 16) {
		DRM_ERROR("UVD IB length (%d) not 16 dwords aligned!\n",
			  ib->length_dw);
		return -EINVAL;
	}

	ctx.parser = parser;
	ctx.buf_sizes = buf_sizes;
	ctx.ib_idx = ib_idx;

	/* first round only required on chips without UVD 64 bit address support */
	if (!parser->adev->uvd.address_64_bit) {
		/* first round, make sure the buffers are actually in the UVD segment */
		r = amdgpu_uvd_cs_packets(&ctx, amdgpu_uvd_cs_pass1);
		if (r)
			return r;
	}

	/* second round, patch buffer addresses into the command stream */
	r = amdgpu_uvd_cs_packets(&ctx, amdgpu_uvd_cs_pass2);
	if (r)
		return r;

	if (!ctx.has_msg_cmd) {
		DRM_ERROR("UVD-IBs need a msg command!\n");
		return -EINVAL;
	}

	return 0;
}