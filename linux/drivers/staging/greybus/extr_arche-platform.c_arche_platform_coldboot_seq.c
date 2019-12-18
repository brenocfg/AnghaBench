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
struct arche_platform_drvdata {scalar_t__ state; int is_reset_act_hi; int /*<<< orphan*/  svc_reset; int /*<<< orphan*/  dev; int /*<<< orphan*/  svc_ref_clk; int /*<<< orphan*/  svc_sysboot; } ;

/* Variables and functions */
 scalar_t__ ARCHE_PLATFORM_STATE_ACTIVE ; 
 int /*<<< orphan*/  arche_platform_set_state (struct arche_platform_drvdata*,scalar_t__) ; 
 int clk_prepare_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  gpiod_set_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svc_reset_onoff (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int
arche_platform_coldboot_seq(struct arche_platform_drvdata *arche_pdata)
{
	int ret;

	if (arche_pdata->state == ARCHE_PLATFORM_STATE_ACTIVE)
		return 0;

	dev_info(arche_pdata->dev, "Booting from cold boot state\n");

	svc_reset_onoff(arche_pdata->svc_reset, arche_pdata->is_reset_act_hi);

	gpiod_set_value(arche_pdata->svc_sysboot, 0);
	usleep_range(100, 200);

	ret = clk_prepare_enable(arche_pdata->svc_ref_clk);
	if (ret) {
		dev_err(arche_pdata->dev, "failed to enable svc_ref_clk: %d\n",
			ret);
		return ret;
	}

	/* bring SVC out of reset */
	svc_reset_onoff(arche_pdata->svc_reset, !arche_pdata->is_reset_act_hi);

	arche_platform_set_state(arche_pdata, ARCHE_PLATFORM_STATE_ACTIVE);

	return 0;
}