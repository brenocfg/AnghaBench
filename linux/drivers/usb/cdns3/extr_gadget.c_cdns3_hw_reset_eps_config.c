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
struct cdns3_device {scalar_t__ wait_for_setup; scalar_t__ out_mem_is_allocated; scalar_t__ onchip_used_size; scalar_t__ hw_configured_flag; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  usb_conf; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_CONF_CFGRST ; 
 int /*<<< orphan*/  cdns3_allow_enable_l1 (struct cdns3_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void cdns3_hw_reset_eps_config(struct cdns3_device *priv_dev)
{
	writel(USB_CONF_CFGRST, &priv_dev->regs->usb_conf);

	cdns3_allow_enable_l1(priv_dev, 0);
	priv_dev->hw_configured_flag = 0;
	priv_dev->onchip_used_size = 0;
	priv_dev->out_mem_is_allocated = 0;
	priv_dev->wait_for_setup = 0;
}