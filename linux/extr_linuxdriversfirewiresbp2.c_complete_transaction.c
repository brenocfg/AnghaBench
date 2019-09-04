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
struct sbp2_orb {int rcode; int /*<<< orphan*/  kref; TYPE_2__* lu; int /*<<< orphan*/  (* callback ) (struct sbp2_orb*,int /*<<< orphan*/ *) ;int /*<<< orphan*/  link; } ;
struct fw_card {int dummy; } ;
struct TYPE_4__ {TYPE_1__* tgt; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int RCODE_COMPLETE ; 
 int /*<<< orphan*/  free_orb ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct sbp2_orb*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void complete_transaction(struct fw_card *card, int rcode,
				 void *payload, size_t length, void *data)
{
	struct sbp2_orb *orb = data;
	unsigned long flags;

	/*
	 * This is a little tricky.  We can get the status write for
	 * the orb before we get this callback.  The status write
	 * handler above will assume the orb pointer transaction was
	 * successful and set the rcode to RCODE_COMPLETE for the orb.
	 * So this callback only sets the rcode if it hasn't already
	 * been set and only does the cleanup if the transaction
	 * failed and we didn't already get a status write.
	 */
	spin_lock_irqsave(&orb->lu->tgt->lock, flags);

	if (orb->rcode == -1)
		orb->rcode = rcode;
	if (orb->rcode != RCODE_COMPLETE) {
		list_del(&orb->link);
		spin_unlock_irqrestore(&orb->lu->tgt->lock, flags);

		orb->callback(orb, NULL);
		kref_put(&orb->kref, free_orb); /* orb callback reference */
	} else {
		spin_unlock_irqrestore(&orb->lu->tgt->lock, flags);
	}

	kref_put(&orb->kref, free_orb); /* transaction callback reference */
}