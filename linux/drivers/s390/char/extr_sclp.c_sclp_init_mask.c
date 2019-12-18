#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int response_code; } ;
struct init_sccb {TYPE_1__ header; } ;
typedef  scalar_t__ sccb_mask_t ;
struct TYPE_5__ {scalar_t__ status; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EIO ; 
 unsigned long HZ ; 
 unsigned long SCLP_BUSY_INTERVAL ; 
 int SCLP_MASK_RETRY ; 
 scalar_t__ SCLP_REQ_DONE ; 
 scalar_t__ SCLP_REQ_FAILED ; 
 int /*<<< orphan*/  __sclp_get_mask (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  __sclp_make_init_req (scalar_t__,scalar_t__) ; 
 unsigned long jiffies ; 
 scalar_t__ sccb_get_sclp_recv_mask (struct init_sccb*) ; 
 scalar_t__ sccb_get_sclp_send_mask (struct init_sccb*) ; 
 scalar_t__ sclp_activation_state ; 
 scalar_t__ sclp_activation_state_inactive ; 
 scalar_t__ sclp_add_request (TYPE_2__*) ; 
 int /*<<< orphan*/  sclp_dispatch_state_change () ; 
 TYPE_2__ sclp_init_req ; 
 struct init_sccb* sclp_init_sccb ; 
 int /*<<< orphan*/  sclp_lock ; 
 scalar_t__ sclp_mask_state ; 
 scalar_t__ sclp_mask_state_idle ; 
 scalar_t__ sclp_mask_state_initializing ; 
 scalar_t__ sclp_receive_mask ; 
 scalar_t__ sclp_send_mask ; 
 int /*<<< orphan*/  sclp_sync_wait () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int
sclp_init_mask(int calculate)
{
	unsigned long flags;
	struct init_sccb *sccb = sclp_init_sccb;
	sccb_mask_t receive_mask;
	sccb_mask_t send_mask;
	int retry;
	int rc;
	unsigned long wait;

	spin_lock_irqsave(&sclp_lock, flags);
	/* Check if interface is in appropriate state */
	if (sclp_mask_state != sclp_mask_state_idle) {
		spin_unlock_irqrestore(&sclp_lock, flags);
		return -EBUSY;
	}
	if (sclp_activation_state == sclp_activation_state_inactive) {
		spin_unlock_irqrestore(&sclp_lock, flags);
		return -EINVAL;
	}
	sclp_mask_state = sclp_mask_state_initializing;
	/* Determine mask */
	if (calculate)
		__sclp_get_mask(&receive_mask, &send_mask);
	else {
		receive_mask = 0;
		send_mask = 0;
	}
	rc = -EIO;
	for (retry = 0; retry <= SCLP_MASK_RETRY; retry++) {
		/* Prepare request */
		__sclp_make_init_req(receive_mask, send_mask);
		spin_unlock_irqrestore(&sclp_lock, flags);
		if (sclp_add_request(&sclp_init_req)) {
			/* Try again later */
			wait = jiffies + SCLP_BUSY_INTERVAL * HZ;
			while (time_before(jiffies, wait))
				sclp_sync_wait();
			spin_lock_irqsave(&sclp_lock, flags);
			continue;
		}
		while (sclp_init_req.status != SCLP_REQ_DONE &&
		       sclp_init_req.status != SCLP_REQ_FAILED)
			sclp_sync_wait();
		spin_lock_irqsave(&sclp_lock, flags);
		if (sclp_init_req.status == SCLP_REQ_DONE &&
		    sccb->header.response_code == 0x20) {
			/* Successful request */
			if (calculate) {
				sclp_receive_mask = sccb_get_sclp_recv_mask(sccb);
				sclp_send_mask = sccb_get_sclp_send_mask(sccb);
			} else {
				sclp_receive_mask = 0;
				sclp_send_mask = 0;
			}
			spin_unlock_irqrestore(&sclp_lock, flags);
			sclp_dispatch_state_change();
			spin_lock_irqsave(&sclp_lock, flags);
			rc = 0;
			break;
		}
	}
	sclp_mask_state = sclp_mask_state_idle;
	spin_unlock_irqrestore(&sclp_lock, flags);
	return rc;
}