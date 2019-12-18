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
struct mdp4_kms {scalar_t__ axi_clk; scalar_t__ lut_clk; scalar_t__ pclk; scalar_t__ clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 

int mdp4_disable(struct mdp4_kms *mdp4_kms)
{
	DBG("");

	clk_disable_unprepare(mdp4_kms->clk);
	if (mdp4_kms->pclk)
		clk_disable_unprepare(mdp4_kms->pclk);
	if (mdp4_kms->lut_clk)
		clk_disable_unprepare(mdp4_kms->lut_clk);
	if (mdp4_kms->axi_clk)
		clk_disable_unprepare(mdp4_kms->axi_clk);

	return 0;
}