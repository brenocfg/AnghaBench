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
struct nv50_clk {int /*<<< orphan*/  hwsq; } ;

/* Variables and functions */
 int clk_exec (int /*<<< orphan*/ *,int) ; 
 struct nv50_clk* nv50_clk (struct nvkm_clk*) ; 

int
nv50_clk_prog(struct nvkm_clk *base)
{
	struct nv50_clk *clk = nv50_clk(base);
	return clk_exec(&clk->hwsq, true);
}