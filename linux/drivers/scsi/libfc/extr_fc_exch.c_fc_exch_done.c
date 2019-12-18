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
struct fc_seq {int dummy; } ;
struct fc_exch {int /*<<< orphan*/  arg; int /*<<< orphan*/  ex_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  fc_exch_delete (struct fc_exch*) ; 
 int fc_exch_done_locked (struct fc_exch*) ; 
 struct fc_exch* fc_seq_exch (struct fc_seq*) ; 
 int /*<<< orphan*/  fc_seq_set_resp (struct fc_seq*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void fc_exch_done(struct fc_seq *sp)
{
	struct fc_exch *ep = fc_seq_exch(sp);
	int rc;

	spin_lock_bh(&ep->ex_lock);
	rc = fc_exch_done_locked(ep);
	spin_unlock_bh(&ep->ex_lock);

	fc_seq_set_resp(sp, NULL, ep->arg);
	if (!rc)
		fc_exch_delete(ep);
}