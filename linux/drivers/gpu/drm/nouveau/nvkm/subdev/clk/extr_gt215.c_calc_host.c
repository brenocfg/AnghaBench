#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct nvkm_cstate {int* domain; } ;
struct gt215_clk_info {int /*<<< orphan*/  host_out; scalar_t__ clk; } ;
struct gt215_clk {int /*<<< orphan*/  base; struct gt215_clk_info* eng; } ;

/* Variables and functions */
 int /*<<< orphan*/  NVA3_HOST_277 ; 
 int /*<<< orphan*/  NVA3_HOST_CLK ; 
 int gt215_clk_info (int /*<<< orphan*/ *,int,int,struct gt215_clk_info*) ; 
 size_t nv_clk_src_host ; 

__attribute__((used)) static int
calc_host(struct gt215_clk *clk, struct nvkm_cstate *cstate)
{
	int ret = 0;
	u32 kHz = cstate->domain[nv_clk_src_host];
	struct gt215_clk_info *info = &clk->eng[nv_clk_src_host];

	if (kHz == 277000) {
		info->clk = 0;
		info->host_out = NVA3_HOST_277;
		return 0;
	}

	info->host_out = NVA3_HOST_CLK;

	ret = gt215_clk_info(&clk->base, 0x1d, kHz, info);
	if (ret >= 0)
		return 0;

	return ret;
}