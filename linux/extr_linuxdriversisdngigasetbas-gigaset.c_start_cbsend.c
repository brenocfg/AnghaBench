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
struct cmdbuf_t {int /*<<< orphan*/  len; int /*<<< orphan*/  buf; } ;
struct TYPE_2__ {struct bas_cardstate* bas; } ;
struct cardstate {int /*<<< orphan*/  cmdlock; struct cmdbuf_t* cmdbuf; int /*<<< orphan*/  bcs; TYPE_1__ hw; } ;
struct bas_cardstate {int basstate; scalar_t__ retry_cmd_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAS_TIMEOUT ; 
 int BS_ATOPEN ; 
 int BS_ATREADY ; 
 int BS_SUSPEND ; 
 int /*<<< orphan*/  DEBUG_OUTPUT ; 
 int EHOSTUNREACH ; 
 int /*<<< orphan*/  HD_OPEN_ATCHANNEL ; 
 int atwrite_submit (struct cardstate*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_cb (struct cardstate*) ; 
 int /*<<< orphan*/  gig_dbg (int /*<<< orphan*/ ,char*) ; 
 int req_submit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int start_cbsend(struct cardstate *cs)
{
	struct cmdbuf_t *cb;
	struct bas_cardstate *ucs = cs->hw.bas;
	unsigned long flags;
	int rc;
	int retval = 0;

	/* check if suspend requested */
	if (ucs->basstate & BS_SUSPEND) {
		gig_dbg(DEBUG_OUTPUT, "suspending");
		return -EHOSTUNREACH;
	}

	/* check if AT channel is open */
	if (!(ucs->basstate & BS_ATOPEN)) {
		gig_dbg(DEBUG_OUTPUT, "AT channel not open");
		rc = req_submit(cs->bcs, HD_OPEN_ATCHANNEL, 0, BAS_TIMEOUT);
		if (rc < 0) {
			/* flush command queue */
			spin_lock_irqsave(&cs->cmdlock, flags);
			while (cs->cmdbuf != NULL)
				complete_cb(cs);
			spin_unlock_irqrestore(&cs->cmdlock, flags);
		}
		return rc;
	}

	/* try to send first command in queue */
	spin_lock_irqsave(&cs->cmdlock, flags);

	while ((cb = cs->cmdbuf) != NULL && (ucs->basstate & BS_ATREADY)) {
		ucs->retry_cmd_out = 0;
		rc = atwrite_submit(cs, cb->buf, cb->len);
		if (unlikely(rc)) {
			retval = rc;
			complete_cb(cs);
		}
	}

	spin_unlock_irqrestore(&cs->cmdlock, flags);
	return retval;
}