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
struct platform_device {int dummy; } ;

/* Variables and functions */
 int imx_scu_get_handle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pinctrl_ipc_handle ; 

int imx_pinctrl_sc_ipc_init(struct platform_device *pdev)
{
	return imx_scu_get_handle(&pinctrl_ipc_handle);
}