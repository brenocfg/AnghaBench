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
typedef  int u16 ;
struct usbhs_priv {int dummy; } ;

/* Variables and functions */
 int CNEN ; 
 int DCFM ; 
 int DPRPU ; 
 int DRPD ; 
 int HSE ; 
 int /*<<< orphan*/  SYSCFG ; 
 int USBE ; 
 int /*<<< orphan*/  has_cnen ; 
 int /*<<< orphan*/  usbhs_bset (struct usbhs_priv*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ usbhs_get_dparam (struct usbhs_priv*,int /*<<< orphan*/ ) ; 

void usbhs_sys_function_ctrl(struct usbhs_priv *priv, int enable)
{
	u16 mask = DCFM | DRPD | DPRPU | HSE | USBE;
	u16 val  = HSE | USBE;

	/* CNEN bit is required for function operation */
	if (usbhs_get_dparam(priv, has_cnen)) {
		mask |= CNEN;
		val  |= CNEN;
	}

	/*
	 * if enable
	 *
	 * - select Function mode
	 * - D+ Line Pull-up is disabled
	 *      When D+ Line Pull-up is enabled,
	 *      calling usbhs_sys_function_pullup(,1)
	 */
	usbhs_bset(priv, SYSCFG, mask, enable ? val : 0);
}