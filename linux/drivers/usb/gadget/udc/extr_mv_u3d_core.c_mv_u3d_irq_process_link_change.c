#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  speed; } ;
struct mv_u3d {int vbus_valid_detect; int /*<<< orphan*/  lock; TYPE_2__ gadget; int /*<<< orphan*/  vbus; void* usb_state; int /*<<< orphan*/  dev; void* resume_state; int /*<<< orphan*/  ep0_state; int /*<<< orphan*/  ep0_dir; TYPE_1__* vuc_regs; } ;
struct TYPE_3__ {int /*<<< orphan*/  ltssmstate; int /*<<< orphan*/  linkchange; } ;

/* Variables and functions */
 int /*<<< orphan*/  MV_U3D_EP_DIR_OUT ; 
 int MV_U3D_LINK_CHANGE_DISABLE_AFTER_U0 ; 
 int MV_U3D_LINK_CHANGE_HRESET ; 
 int MV_U3D_LINK_CHANGE_INACT ; 
 int MV_U3D_LINK_CHANGE_LINK_UP ; 
 int MV_U3D_LINK_CHANGE_RESUME ; 
 int MV_U3D_LINK_CHANGE_SUSPEND ; 
 int MV_U3D_LINK_CHANGE_VBUS_INVALID ; 
 int MV_U3D_LINK_CHANGE_WRESET ; 
 int /*<<< orphan*/  MV_U3D_WAIT_FOR_SETUP ; 
 int /*<<< orphan*/  USB_SPEED_SUPER ; 
 void* USB_STATE_ATTACHED ; 
 void* USB_STATE_DEFAULT ; 
 void* USB_STATE_POWERED ; 
 void* USB_STATE_SUSPENDED ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int ioread32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iowrite32 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mv_u3d_vbus_session (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mv_u3d_irq_process_link_change(struct mv_u3d *u3d)
{
	u32 linkchange;

	linkchange = ioread32(&u3d->vuc_regs->linkchange);
	iowrite32(linkchange, &u3d->vuc_regs->linkchange);

	dev_dbg(u3d->dev, "linkchange: 0x%x\n", linkchange);

	if (linkchange & MV_U3D_LINK_CHANGE_LINK_UP) {
		dev_dbg(u3d->dev, "link up: ltssm state: 0x%x\n",
			ioread32(&u3d->vuc_regs->ltssmstate));

		u3d->usb_state = USB_STATE_DEFAULT;
		u3d->ep0_dir = MV_U3D_EP_DIR_OUT;
		u3d->ep0_state = MV_U3D_WAIT_FOR_SETUP;

		/* set speed */
		u3d->gadget.speed = USB_SPEED_SUPER;
	}

	if (linkchange & MV_U3D_LINK_CHANGE_SUSPEND) {
		dev_dbg(u3d->dev, "link suspend\n");
		u3d->resume_state = u3d->usb_state;
		u3d->usb_state = USB_STATE_SUSPENDED;
	}

	if (linkchange & MV_U3D_LINK_CHANGE_RESUME) {
		dev_dbg(u3d->dev, "link resume\n");
		u3d->usb_state = u3d->resume_state;
		u3d->resume_state = 0;
	}

	if (linkchange & MV_U3D_LINK_CHANGE_WRESET) {
		dev_dbg(u3d->dev, "warm reset\n");
		u3d->usb_state = USB_STATE_POWERED;
	}

	if (linkchange & MV_U3D_LINK_CHANGE_HRESET) {
		dev_dbg(u3d->dev, "hot reset\n");
		u3d->usb_state = USB_STATE_DEFAULT;
	}

	if (linkchange & MV_U3D_LINK_CHANGE_INACT)
		dev_dbg(u3d->dev, "inactive\n");

	if (linkchange & MV_U3D_LINK_CHANGE_DISABLE_AFTER_U0)
		dev_dbg(u3d->dev, "ss.disabled\n");

	if (linkchange & MV_U3D_LINK_CHANGE_VBUS_INVALID) {
		dev_dbg(u3d->dev, "vbus invalid\n");
		u3d->usb_state = USB_STATE_ATTACHED;
		u3d->vbus_valid_detect = 1;
		/* if external vbus detect is not supported,
		 * we handle it here.
		 */
		if (!u3d->vbus) {
			spin_unlock(&u3d->lock);
			mv_u3d_vbus_session(&u3d->gadget, 0);
			spin_lock(&u3d->lock);
		}
	}
}