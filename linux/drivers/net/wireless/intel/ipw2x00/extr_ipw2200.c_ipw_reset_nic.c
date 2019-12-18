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
struct ipw_priv {int status; int /*<<< orphan*/  lock; int /*<<< orphan*/  wait_state; int /*<<< orphan*/  wait_command_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPW_DEBUG_TRACE (char*) ; 
 int STATUS_HCMD_ACTIVE ; 
 int STATUS_SCANNING ; 
 int STATUS_SCAN_ABORTING ; 
 int ipw_init_nic (struct ipw_priv*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ipw_reset_nic(struct ipw_priv *priv)
{
	int rc = 0;
	unsigned long flags;

	IPW_DEBUG_TRACE(">>\n");

	rc = ipw_init_nic(priv);

	spin_lock_irqsave(&priv->lock, flags);
	/* Clear the 'host command active' bit... */
	priv->status &= ~STATUS_HCMD_ACTIVE;
	wake_up_interruptible(&priv->wait_command_queue);
	priv->status &= ~(STATUS_SCANNING | STATUS_SCAN_ABORTING);
	wake_up_interruptible(&priv->wait_state);
	spin_unlock_irqrestore(&priv->lock, flags);

	IPW_DEBUG_TRACE("<<\n");
	return rc;
}