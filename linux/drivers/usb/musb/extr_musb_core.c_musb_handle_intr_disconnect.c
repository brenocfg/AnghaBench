#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct musb {TYPE_4__* xceiv; TYPE_2__* hcd; int /*<<< orphan*/  a_wait_bcon; } ;
struct TYPE_8__ {TYPE_3__* otg; } ;
struct TYPE_7__ {int state; } ;
struct TYPE_5__ {int /*<<< orphan*/  is_b_host; } ;
struct TYPE_6__ {TYPE_1__ self; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_DEV_MODE (struct musb*) ; 
 int /*<<< orphan*/  MUSB_MODE (struct musb*) ; 
#define  OTG_STATE_A_HOST 134 
#define  OTG_STATE_A_PERIPHERAL 133 
#define  OTG_STATE_A_SUSPEND 132 
#define  OTG_STATE_B_HOST 131 
#define  OTG_STATE_B_IDLE 130 
#define  OTG_STATE_B_PERIPHERAL 129 
#define  OTG_STATE_B_WAIT_ACON 128 
 int /*<<< orphan*/  WARNING (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_dbg (struct musb*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_g_disconnect (struct musb*) ; 
 int /*<<< orphan*/  musb_hnp_stop (struct musb*) ; 
 int /*<<< orphan*/  musb_host_resume_root_hub (struct musb*) ; 
 int /*<<< orphan*/  musb_platform_try_idle (struct musb*,scalar_t__) ; 
 int /*<<< orphan*/  musb_root_disconnect (struct musb*) ; 
 int /*<<< orphan*/  usb_otg_state_string (int) ; 

__attribute__((used)) static void musb_handle_intr_disconnect(struct musb *musb, u8 devctl)
{
	musb_dbg(musb, "DISCONNECT (%s) as %s, devctl %02x",
			usb_otg_state_string(musb->xceiv->otg->state),
			MUSB_MODE(musb), devctl);

	switch (musb->xceiv->otg->state) {
	case OTG_STATE_A_HOST:
	case OTG_STATE_A_SUSPEND:
		musb_host_resume_root_hub(musb);
		musb_root_disconnect(musb);
		if (musb->a_wait_bcon != 0)
			musb_platform_try_idle(musb, jiffies
				+ msecs_to_jiffies(musb->a_wait_bcon));
		break;
	case OTG_STATE_B_HOST:
		/* REVISIT this behaves for "real disconnect"
		 * cases; make sure the other transitions from
		 * from B_HOST act right too.  The B_HOST code
		 * in hnp_stop() is currently not used...
		 */
		musb_root_disconnect(musb);
		if (musb->hcd)
			musb->hcd->self.is_b_host = 0;
		musb->xceiv->otg->state = OTG_STATE_B_PERIPHERAL;
		MUSB_DEV_MODE(musb);
		musb_g_disconnect(musb);
		break;
	case OTG_STATE_A_PERIPHERAL:
		musb_hnp_stop(musb);
		musb_root_disconnect(musb);
		/* FALLTHROUGH */
	case OTG_STATE_B_WAIT_ACON:
		/* FALLTHROUGH */
	case OTG_STATE_B_PERIPHERAL:
	case OTG_STATE_B_IDLE:
		musb_g_disconnect(musb);
		break;
	default:
		WARNING("unhandled DISCONNECT transition (%s)\n",
			usb_otg_state_string(musb->xceiv->otg->state));
		break;
	}
}