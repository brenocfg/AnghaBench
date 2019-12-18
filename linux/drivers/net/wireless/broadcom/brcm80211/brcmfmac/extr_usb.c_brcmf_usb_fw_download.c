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
typedef  int /*<<< orphan*/  u8 ;
struct brcmf_usbdev_info {int /*<<< orphan*/  image_len; scalar_t__ image; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOENT ; 
 int /*<<< orphan*/  USB ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  brcmf_err (char*) ; 
 int brcmf_usb_dlrun (struct brcmf_usbdev_info*) ; 
 int brcmf_usb_dlstart (struct brcmf_usbdev_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
brcmf_usb_fw_download(struct brcmf_usbdev_info *devinfo)
{
	int err;

	brcmf_dbg(USB, "Enter\n");
	if (devinfo == NULL)
		return -ENODEV;

	if (!devinfo->image) {
		brcmf_err("No firmware!\n");
		return -ENOENT;
	}

	err = brcmf_usb_dlstart(devinfo,
		(u8 *)devinfo->image, devinfo->image_len);
	if (err == 0)
		err = brcmf_usb_dlrun(devinfo);
	return err;
}