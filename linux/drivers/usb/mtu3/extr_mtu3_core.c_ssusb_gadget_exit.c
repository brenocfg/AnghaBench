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
struct ssusb_mtk {int /*<<< orphan*/  dev; struct mtu3* u3d; } ;
struct mtu3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_init_wakeup (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtu3_gadget_cleanup (struct mtu3*) ; 
 int /*<<< orphan*/  mtu3_hw_exit (struct mtu3*) ; 

void ssusb_gadget_exit(struct ssusb_mtk *ssusb)
{
	struct mtu3 *mtu = ssusb->u3d;

	mtu3_gadget_cleanup(mtu);
	device_init_wakeup(ssusb->dev, false);
	mtu3_hw_exit(mtu);
}