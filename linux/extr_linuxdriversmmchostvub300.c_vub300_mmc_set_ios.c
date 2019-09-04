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
struct vub300_mmc_host {int card_powered; int /*<<< orphan*/  kref; int /*<<< orphan*/  cmd_mutex; int /*<<< orphan*/  udev; int /*<<< orphan*/  interface; } ;
struct mmc_ios {scalar_t__ power_mode; } ;
struct mmc_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HZ ; 
 scalar_t__ MMC_POWER_OFF ; 
 scalar_t__ MMC_POWER_ON ; 
 scalar_t__ MMC_POWER_UP ; 
 int /*<<< orphan*/  SET_SD_POWER ; 
 int USB_DIR_OUT ; 
 int USB_RECIP_DEVICE ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  __set_clock_speed (struct vub300_mmc_host*,int /*<<< orphan*/ *,struct mmc_ios*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct vub300_mmc_host* mmc_priv (struct mmc_host*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_control_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_sndctrlpipe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vub300_delete ; 

__attribute__((used)) static void vub300_mmc_set_ios(struct mmc_host *mmc, struct mmc_ios *ios)
{				/* NOT irq */
	struct vub300_mmc_host *vub300 = mmc_priv(mmc);
	if (!vub300->interface)
		return;
	kref_get(&vub300->kref);
	mutex_lock(&vub300->cmd_mutex);
	if ((ios->power_mode == MMC_POWER_OFF) && vub300->card_powered) {
		vub300->card_powered = 0;
		usb_control_msg(vub300->udev, usb_sndctrlpipe(vub300->udev, 0),
				SET_SD_POWER,
				USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				0x0000, 0x0000, NULL, 0, HZ);
		/* must wait for the VUB300 u-proc to boot up */
		msleep(600);
	} else if ((ios->power_mode == MMC_POWER_UP) && !vub300->card_powered) {
		usb_control_msg(vub300->udev, usb_sndctrlpipe(vub300->udev, 0),
				SET_SD_POWER,
				USB_DIR_OUT | USB_TYPE_VENDOR | USB_RECIP_DEVICE,
				0x0001, 0x0000, NULL, 0, HZ);
		msleep(600);
		vub300->card_powered = 1;
	} else if (ios->power_mode == MMC_POWER_ON) {
		u8 *buf = kmalloc(8, GFP_KERNEL);
		if (buf) {
			__set_clock_speed(vub300, buf, ios);
			kfree(buf);
		}
	} else {
		/* this should mean no change of state */
	}
	mutex_unlock(&vub300->cmd_mutex);
	kref_put(&vub300->kref, vub300_delete);
}