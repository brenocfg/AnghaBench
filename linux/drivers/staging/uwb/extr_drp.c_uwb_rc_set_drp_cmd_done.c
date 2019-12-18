#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct uwb_rceb {int dummy; } ;
struct uwb_rc_evt_set_drp_ie {scalar_t__ bResultCode; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct uwb_rc {int set_drp_ie_pending; int /*<<< orphan*/  rsvs_lock; TYPE_1__ uwb_dev; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 scalar_t__ UWB_RC_RES_SUCCESS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  uwb_rc_strerror (scalar_t__) ; 
 int /*<<< orphan*/  uwb_rsv_queue_update (struct uwb_rc*) ; 

__attribute__((used)) static void uwb_rc_set_drp_cmd_done(struct uwb_rc *rc, void *arg,
				    struct uwb_rceb *reply, ssize_t reply_size)
{
	struct uwb_rc_evt_set_drp_ie *r = (struct uwb_rc_evt_set_drp_ie *)reply;
	unsigned long flags;

	if (r != NULL) {
		if (r->bResultCode != UWB_RC_RES_SUCCESS)
			dev_err(&rc->uwb_dev.dev, "SET-DRP-IE failed: %s (%d)\n",
				uwb_rc_strerror(r->bResultCode), r->bResultCode);
	} else
		dev_err(&rc->uwb_dev.dev, "SET-DRP-IE: timeout\n");

	spin_lock_irqsave(&rc->rsvs_lock, flags);
	if (rc->set_drp_ie_pending > 1) {
		rc->set_drp_ie_pending = 0;
		uwb_rsv_queue_update(rc);
	} else {
		rc->set_drp_ie_pending = 0;
	}
	spin_unlock_irqrestore(&rc->rsvs_lock, flags);
}