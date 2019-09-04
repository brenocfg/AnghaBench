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
struct nvkm_pll_vals {int M1; int M2; int N1; int N2; int refclk; int log2P; } ;

/* Variables and functions */

int
nouveau_hw_pllvals_to_clk(struct nvkm_pll_vals *pv)
{
	/* Avoid divide by zero if called at an inappropriate time */
	if (!pv->M1 || !pv->M2)
		return 0;

	return pv->N1 * pv->N2 * pv->refclk / (pv->M1 * pv->M2) >> pv->log2P;
}