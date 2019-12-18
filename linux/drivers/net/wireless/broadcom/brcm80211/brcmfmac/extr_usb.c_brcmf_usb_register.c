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

/* Variables and functions */
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_err (char*,int) ; 
 int /*<<< orphan*/  brcmf_usbdrvr ; 
 int usb_register (int /*<<< orphan*/ *) ; 

void brcmf_usb_register(void)
{
	int ret;

	brcmf_dbg(USB, "Enter\n");
	ret = usb_register(&brcmf_usbdrvr);
	if (ret)
		brcmf_err("usb_register failed %d\n", ret);
}