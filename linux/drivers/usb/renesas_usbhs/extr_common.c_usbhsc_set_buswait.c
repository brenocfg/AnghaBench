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
 int /*<<< orphan*/  BUSWAIT ; 
 int /*<<< orphan*/  buswait_bwait ; 
 int /*<<< orphan*/  usbhs_bset (struct usbhs_priv*,int /*<<< orphan*/ ,int,int) ; 
 int usbhs_get_dparam (struct usbhs_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void usbhsc_set_buswait(struct usbhs_priv *priv)
{
	int wait = usbhs_get_dparam(priv, buswait_bwait);

	/* set bus wait if platform have */
	if (wait)
		usbhs_bset(priv, BUSWAIT, 0x000F, wait);
}