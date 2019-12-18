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
typedef  int u32 ;
struct usb_hcd {int /*<<< orphan*/  regs; int /*<<< orphan*/  state; } ;
struct isp1760_hcd {int /*<<< orphan*/  lock; int /*<<< orphan*/  reset_done; } ;

/* Variables and functions */
 int /*<<< orphan*/  HC_IS_RUNNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HC_PORTSC1 ; 
 int PORT_CSC ; 
 int PORT_OWNER ; 
 int PORT_RESUME ; 
 int STS_PCD ; 
 struct isp1760_hcd* hcd_to_priv (struct usb_hcd*) ; 
 int /*<<< orphan*/  jiffies ; 
 int reg_read32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_write32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_after_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int isp1760_hub_status_data(struct usb_hcd *hcd, char *buf)
{
	struct isp1760_hcd *priv = hcd_to_priv(hcd);
	u32 temp, status = 0;
	u32 mask;
	int retval = 1;
	unsigned long flags;

	/* if !PM, root hub timers won't get shut down ... */
	if (!HC_IS_RUNNING(hcd->state))
		return 0;

	/* init status to no-changes */
	buf[0] = 0;
	mask = PORT_CSC;

	spin_lock_irqsave(&priv->lock, flags);
	temp = reg_read32(hcd->regs, HC_PORTSC1);

	if (temp & PORT_OWNER) {
		if (temp & PORT_CSC) {
			temp &= ~PORT_CSC;
			reg_write32(hcd->regs, HC_PORTSC1, temp);
			goto done;
		}
	}

	/*
	 * Return status information even for ports with OWNER set.
	 * Otherwise hub_wq wouldn't see the disconnect event when a
	 * high-speed device is switched over to the companion
	 * controller by the user.
	 */

	if ((temp & mask) != 0
			|| ((temp & PORT_RESUME) != 0
				&& time_after_eq(jiffies,
					priv->reset_done))) {
		buf [0] |= 1 << (0 + 1);
		status = STS_PCD;
	}
	/* FIXME autosuspend idle root hubs */
done:
	spin_unlock_irqrestore(&priv->lock, flags);
	return status ? retval : 0;
}