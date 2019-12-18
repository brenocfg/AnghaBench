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
struct mdp5_kms {scalar_t__ enable_count; scalar_t__ lut_clk; scalar_t__ core_clk; scalar_t__ axi_clk; scalar_t__ ahb_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  clk_disable_unprepare (scalar_t__) ; 

int mdp5_disable(struct mdp5_kms *mdp5_kms)
{
	DBG("");

	mdp5_kms->enable_count--;
	WARN_ON(mdp5_kms->enable_count < 0);

	clk_disable_unprepare(mdp5_kms->ahb_clk);
	clk_disable_unprepare(mdp5_kms->axi_clk);
	clk_disable_unprepare(mdp5_kms->core_clk);
	if (mdp5_kms->lut_clk)
		clk_disable_unprepare(mdp5_kms->lut_clk);

	return 0;
}