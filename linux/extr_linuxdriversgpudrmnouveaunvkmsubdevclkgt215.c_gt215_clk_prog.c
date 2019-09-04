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
struct nvkm_clk {int dummy; } ;
struct gt215_clk_info {scalar_t__ pll; } ;
struct gt215_clk {int /*<<< orphan*/  base; struct gt215_clk_info* eng; } ;

/* Variables and functions */
 int EBUSY ; 
 struct gt215_clk* gt215_clk (struct nvkm_clk*) ; 
 int /*<<< orphan*/  gt215_clk_post (int /*<<< orphan*/ *,unsigned long*) ; 
 int gt215_clk_pre (int /*<<< orphan*/ *,unsigned long*) ; 
 size_t nv_clk_src_core ; 
 size_t nv_clk_src_core_intm ; 
 int /*<<< orphan*/  nv_clk_src_disp ; 
 int /*<<< orphan*/  nv_clk_src_shader ; 
 int /*<<< orphan*/  nv_clk_src_vdec ; 
 int /*<<< orphan*/  prog_clk (struct gt215_clk*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prog_core (struct gt215_clk*,size_t) ; 
 int /*<<< orphan*/  prog_host (struct gt215_clk*) ; 
 int /*<<< orphan*/  prog_pll (struct gt215_clk*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
gt215_clk_prog(struct nvkm_clk *base)
{
	struct gt215_clk *clk = gt215_clk(base);
	struct gt215_clk_info *core = &clk->eng[nv_clk_src_core];
	int ret = 0;
	unsigned long flags;
	unsigned long *f = &flags;

	ret = gt215_clk_pre(&clk->base, f);
	if (ret)
		goto out;

	if (core->pll)
		prog_core(clk, nv_clk_src_core_intm);

	prog_core(clk,  nv_clk_src_core);
	prog_pll(clk, 0x01, 0x004220, nv_clk_src_shader);
	prog_clk(clk, 0x20, nv_clk_src_disp);
	prog_clk(clk, 0x21, nv_clk_src_vdec);
	prog_host(clk);

out:
	if (ret == -EBUSY)
		f = NULL;

	gt215_clk_post(&clk->base, f);
	return ret;
}