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
struct nvkm_cstate {int* domain; } ;
struct nvkm_clk {int dummy; } ;
struct nv40_clk {int npll_ctrl; int npll_coef; int spll; int ctrl; } ;

/* Variables and functions */
 struct nv40_clk* nv40_clk (struct nvkm_clk*) ; 
 int nv40_clk_calc_pll (struct nv40_clk*,int,int,int*,int*,int*,int*,int*) ; 
 size_t nv_clk_src_core ; 
 size_t nv_clk_src_shader ; 

__attribute__((used)) static int
nv40_clk_calc(struct nvkm_clk *base, struct nvkm_cstate *cstate)
{
	struct nv40_clk *clk = nv40_clk(base);
	int gclk = cstate->domain[nv_clk_src_core];
	int sclk = cstate->domain[nv_clk_src_shader];
	int N1, M1, N2, M2, log2P;
	int ret;

	/* core/geometric clock */
	ret = nv40_clk_calc_pll(clk, 0x004000, gclk,
				&N1, &M1, &N2, &M2, &log2P);
	if (ret < 0)
		return ret;

	if (N2 == M2) {
		clk->npll_ctrl = 0x80000100 | (log2P << 16);
		clk->npll_coef = (N1 << 8) | M1;
	} else {
		clk->npll_ctrl = 0xc0000000 | (log2P << 16);
		clk->npll_coef = (N2 << 24) | (M2 << 16) | (N1 << 8) | M1;
	}

	/* use the second pll for shader/rop clock, if it differs from core */
	if (sclk && sclk != gclk) {
		ret = nv40_clk_calc_pll(clk, 0x004008, sclk,
					&N1, &M1, NULL, NULL, &log2P);
		if (ret < 0)
			return ret;

		clk->spll = 0xc0000000 | (log2P << 16) | (N1 << 8) | M1;
		clk->ctrl = 0x00000223;
	} else {
		clk->spll = 0x00000000;
		clk->ctrl = 0x00000333;
	}

	return 0;
}