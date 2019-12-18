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
struct adapter {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * pno_ssid_list; int /*<<< orphan*/ * pscan_info; int /*<<< orphan*/ * pnlo_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*) ; 
 TYPE_1__* pwrctrlpriv ; 

void rtw_free_pwrctrl_priv(struct adapter *adapter)
{
#ifdef CONFIG_PNO_SUPPORT
	if (pwrctrlpriv->pnlo_info != NULL)
		printk("****** pnlo_info memory leak********\n");

	if (pwrctrlpriv->pscan_info != NULL)
		printk("****** pscan_info memory leak********\n");

	if (pwrctrlpriv->pno_ssid_list != NULL)
		printk("****** pno_ssid_list memory leak********\n");
#endif
}