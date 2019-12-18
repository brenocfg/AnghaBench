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
struct notifier_block {int dummy; } ;

/* Variables and functions */
 int NOTIFY_OK ; 
 int /*<<< orphan*/  ifx_modem_power_off (scalar_t__) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 scalar_t__ saved_ifx_dev ; 

__attribute__((used)) static int ifx_modem_reboot_callback(struct notifier_block *nfb,
				 unsigned long event, void *data)
{
	if (saved_ifx_dev)
		ifx_modem_power_off(saved_ifx_dev);
	else
		pr_warn("no ifx modem active;\n");

	return NOTIFY_OK;
}