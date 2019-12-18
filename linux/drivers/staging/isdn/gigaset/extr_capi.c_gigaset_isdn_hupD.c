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
struct gigaset_capi_appl {struct gigaset_capi_appl* bcnext; } ;
struct bc_state {int /*<<< orphan*/  aplock; int /*<<< orphan*/  apconnstate; struct gigaset_capi_appl* ap; } ;

/* Variables and functions */
 int /*<<< orphan*/  APCONN_NONE ; 
 int /*<<< orphan*/  send_disconnect_b3_ind (struct bc_state*,struct gigaset_capi_appl*) ; 
 int /*<<< orphan*/  send_disconnect_ind (struct bc_state*,struct gigaset_capi_appl*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void gigaset_isdn_hupD(struct bc_state *bcs)
{
	struct gigaset_capi_appl *ap;
	unsigned long flags;

	/*
	 * ToDo: pass on reason code reported by device
	 * (requires ev-layer state machine extension to collect
	 * ZCAU device reply)
	 */
	spin_lock_irqsave(&bcs->aplock, flags);
	while (bcs->ap != NULL) {
		ap = bcs->ap;
		bcs->ap = ap->bcnext;
		spin_unlock_irqrestore(&bcs->aplock, flags);
		send_disconnect_b3_ind(bcs, ap);
		send_disconnect_ind(bcs, ap, 0);
		spin_lock_irqsave(&bcs->aplock, flags);
	}
	bcs->apconnstate = APCONN_NONE;
	spin_unlock_irqrestore(&bcs->aplock, flags);
}