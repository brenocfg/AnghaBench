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
struct palmas {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PALMAS_USB_OTG_BASE ; 
 int /*<<< orphan*/  PALMAS_USB_WAKEUP ; 
 int /*<<< orphan*/  PALMAS_USB_WAKEUP_ID_WK_UP_COMP ; 
 int /*<<< orphan*/  palmas_write (struct palmas*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void palmas_usb_wakeup(struct palmas *palmas, int enable)
{
	if (enable)
		palmas_write(palmas, PALMAS_USB_OTG_BASE, PALMAS_USB_WAKEUP,
			PALMAS_USB_WAKEUP_ID_WK_UP_COMP);
	else
		palmas_write(palmas, PALMAS_USB_OTG_BASE, PALMAS_USB_WAKEUP, 0);
}