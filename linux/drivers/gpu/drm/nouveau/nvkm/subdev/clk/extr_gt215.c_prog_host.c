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
typedef  int u32 ;
struct nvkm_device {int dummy; } ;
struct gt215_clk_info {int host_out; } ;
struct TYPE_3__ {struct nvkm_device* device; } ;
struct TYPE_4__ {TYPE_1__ subdev; } ;
struct gt215_clk {TYPE_2__ base; struct gt215_clk_info* eng; } ;

/* Variables and functions */
#define  NVA3_HOST_277 129 
#define  NVA3_HOST_CLK 128 
 int /*<<< orphan*/  disable_clk_src (struct gt215_clk*,int) ; 
 size_t nv_clk_src_host ; 
 int nvkm_rd32 (struct nvkm_device*,int) ; 
 int /*<<< orphan*/  nvkm_wr32 (struct nvkm_device*,int,int) ; 
 int /*<<< orphan*/  prog_clk (struct gt215_clk*,int,size_t) ; 

__attribute__((used)) static void
prog_host(struct gt215_clk *clk)
{
	struct gt215_clk_info *info = &clk->eng[nv_clk_src_host];
	struct nvkm_device *device = clk->base.subdev.device;
	u32 hsrc = (nvkm_rd32(device, 0xc040));

	switch (info->host_out) {
	case NVA3_HOST_277:
		if ((hsrc & 0x30000000) == 0) {
			nvkm_wr32(device, 0xc040, hsrc | 0x20000000);
			disable_clk_src(clk, 0x4194);
		}
		break;
	case NVA3_HOST_CLK:
		prog_clk(clk, 0x1d, nv_clk_src_host);
		if ((hsrc & 0x30000000) >= 0x20000000) {
			nvkm_wr32(device, 0xc040, hsrc & ~0x30000000);
		}
		break;
	default:
		break;
	}

	/* This seems to be a clock gating factor on idle, always set to 64 */
	nvkm_wr32(device, 0xc044, 0x3e);
}