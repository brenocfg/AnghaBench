#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct tg3 {int grc_local_ctrl; int nic_sram_data_cfg; TYPE_1__* pdev; } ;
struct TYPE_2__ {scalar_t__ device; } ;

/* Variables and functions */
 scalar_t__ ASIC_REV_5700 ; 
 scalar_t__ ASIC_REV_5701 ; 
 scalar_t__ ASIC_REV_5714 ; 
 int GRC_LCLCTRL_GPIO_OE0 ; 
 int GRC_LCLCTRL_GPIO_OE1 ; 
 int GRC_LCLCTRL_GPIO_OE2 ; 
 int GRC_LCLCTRL_GPIO_OE3 ; 
 int GRC_LCLCTRL_GPIO_OUTPUT0 ; 
 int GRC_LCLCTRL_GPIO_OUTPUT1 ; 
 int GRC_LCLCTRL_GPIO_OUTPUT2 ; 
 int /*<<< orphan*/  GRC_LOCAL_CTRL ; 
 int /*<<< orphan*/  IS_NIC ; 
 int NIC_SRAM_DATA_CFG_NO_GPIO2 ; 
 scalar_t__ PCI_DEVICE_ID_TIGON3_5761 ; 
 scalar_t__ TG3PCI_DEVICE_TIGON3_5761S ; 
 int /*<<< orphan*/  TG3_GRC_LCLCTL_PWRSW_DELAY ; 
 scalar_t__ tg3_asic_rev (struct tg3*) ; 
 int /*<<< orphan*/  tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32_wait_f (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_pwrsrc_switch_to_vaux(struct tg3 *tp)
{
	if (!tg3_flag(tp, IS_NIC))
		return;

	if (tg3_asic_rev(tp) == ASIC_REV_5700 ||
	    tg3_asic_rev(tp) == ASIC_REV_5701) {
		tw32_wait_f(GRC_LOCAL_CTRL, tp->grc_local_ctrl |
			    (GRC_LCLCTRL_GPIO_OE0 |
			     GRC_LCLCTRL_GPIO_OE1 |
			     GRC_LCLCTRL_GPIO_OE2 |
			     GRC_LCLCTRL_GPIO_OUTPUT0 |
			     GRC_LCLCTRL_GPIO_OUTPUT1),
			    TG3_GRC_LCLCTL_PWRSW_DELAY);
	} else if (tp->pdev->device == PCI_DEVICE_ID_TIGON3_5761 ||
		   tp->pdev->device == TG3PCI_DEVICE_TIGON3_5761S) {
		/* The 5761 non-e device swaps GPIO 0 and GPIO 2. */
		u32 grc_local_ctrl = GRC_LCLCTRL_GPIO_OE0 |
				     GRC_LCLCTRL_GPIO_OE1 |
				     GRC_LCLCTRL_GPIO_OE2 |
				     GRC_LCLCTRL_GPIO_OUTPUT0 |
				     GRC_LCLCTRL_GPIO_OUTPUT1 |
				     tp->grc_local_ctrl;
		tw32_wait_f(GRC_LOCAL_CTRL, grc_local_ctrl,
			    TG3_GRC_LCLCTL_PWRSW_DELAY);

		grc_local_ctrl |= GRC_LCLCTRL_GPIO_OUTPUT2;
		tw32_wait_f(GRC_LOCAL_CTRL, grc_local_ctrl,
			    TG3_GRC_LCLCTL_PWRSW_DELAY);

		grc_local_ctrl &= ~GRC_LCLCTRL_GPIO_OUTPUT0;
		tw32_wait_f(GRC_LOCAL_CTRL, grc_local_ctrl,
			    TG3_GRC_LCLCTL_PWRSW_DELAY);
	} else {
		u32 no_gpio2;
		u32 grc_local_ctrl = 0;

		/* Workaround to prevent overdrawing Amps. */
		if (tg3_asic_rev(tp) == ASIC_REV_5714) {
			grc_local_ctrl |= GRC_LCLCTRL_GPIO_OE3;
			tw32_wait_f(GRC_LOCAL_CTRL, tp->grc_local_ctrl |
				    grc_local_ctrl,
				    TG3_GRC_LCLCTL_PWRSW_DELAY);
		}

		/* On 5753 and variants, GPIO2 cannot be used. */
		no_gpio2 = tp->nic_sram_data_cfg &
			   NIC_SRAM_DATA_CFG_NO_GPIO2;

		grc_local_ctrl |= GRC_LCLCTRL_GPIO_OE0 |
				  GRC_LCLCTRL_GPIO_OE1 |
				  GRC_LCLCTRL_GPIO_OE2 |
				  GRC_LCLCTRL_GPIO_OUTPUT1 |
				  GRC_LCLCTRL_GPIO_OUTPUT2;
		if (no_gpio2) {
			grc_local_ctrl &= ~(GRC_LCLCTRL_GPIO_OE2 |
					    GRC_LCLCTRL_GPIO_OUTPUT2);
		}
		tw32_wait_f(GRC_LOCAL_CTRL,
			    tp->grc_local_ctrl | grc_local_ctrl,
			    TG3_GRC_LCLCTL_PWRSW_DELAY);

		grc_local_ctrl |= GRC_LCLCTRL_GPIO_OUTPUT0;

		tw32_wait_f(GRC_LOCAL_CTRL,
			    tp->grc_local_ctrl | grc_local_ctrl,
			    TG3_GRC_LCLCTL_PWRSW_DELAY);

		if (!no_gpio2) {
			grc_local_ctrl &= ~GRC_LCLCTRL_GPIO_OUTPUT2;
			tw32_wait_f(GRC_LOCAL_CTRL,
				    tp->grc_local_ctrl | grc_local_ctrl,
				    TG3_GRC_LCLCTL_PWRSW_DELAY);
		}
	}
}