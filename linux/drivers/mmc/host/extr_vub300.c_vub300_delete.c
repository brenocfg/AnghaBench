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
struct vub300_mmc_host {int /*<<< orphan*/  udev; int /*<<< orphan*/ * command_res_urb; int /*<<< orphan*/ * command_out_urb; struct mmc_host* mmc; } ;
struct mmc_host {int dummy; } ;
struct kref {int dummy; } ;

/* Variables and functions */
 struct vub300_mmc_host* kref_to_vub300_mmc_host (struct kref*) ; 
 int /*<<< orphan*/  mmc_free_host (struct mmc_host*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_put_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vub300_delete(struct kref *kref)
{				/* kref callback - softirq */
	struct vub300_mmc_host *vub300 = kref_to_vub300_mmc_host(kref);
	struct mmc_host *mmc = vub300->mmc;
	usb_free_urb(vub300->command_out_urb);
	vub300->command_out_urb = NULL;
	usb_free_urb(vub300->command_res_urb);
	vub300->command_res_urb = NULL;
	usb_put_dev(vub300->udev);
	mmc_free_host(mmc);
	/*
	 * and hence also frees vub300
	 * which is contained at the end of struct mmc
	 */
}