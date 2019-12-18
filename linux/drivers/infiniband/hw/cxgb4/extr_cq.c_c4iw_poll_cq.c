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
struct ib_wc {int dummy; } ;
struct ib_cq {int dummy; } ;
struct c4iw_cq {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EAGAIN ; 
 int ENODATA ; 
 int c4iw_poll_cq_one (struct c4iw_cq*,struct ib_wc*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct c4iw_cq* to_c4iw_cq (struct ib_cq*) ; 

int c4iw_poll_cq(struct ib_cq *ibcq, int num_entries, struct ib_wc *wc)
{
	struct c4iw_cq *chp;
	unsigned long flags;
	int npolled;
	int err = 0;

	chp = to_c4iw_cq(ibcq);

	spin_lock_irqsave(&chp->lock, flags);
	for (npolled = 0; npolled < num_entries; ++npolled) {
		do {
			err = c4iw_poll_cq_one(chp, wc + npolled);
		} while (err == -EAGAIN);
		if (err)
			break;
	}
	spin_unlock_irqrestore(&chp->lock, flags);
	return !err || err == -ENODATA ? npolled : err;
}