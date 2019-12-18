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
struct usbhs_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRPU ; 
 int /*<<< orphan*/  SYSCFG ; 
 int /*<<< orphan*/  usbhs_bset (struct usbhs_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void usbhs_sys_function_pullup(struct usbhs_priv *priv, int enable)
{
	usbhs_bset(priv, SYSCFG, DPRPU, enable ? DPRPU : 0);
}