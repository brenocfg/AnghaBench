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
struct l2t_entry {scalar_t__ state; int /*<<< orphan*/  lock; TYPE_1__* neigh; } ;
struct l2t_data {unsigned int l2t_start; struct l2t_entry* l2tab; } ;
struct cpl_l2t_write_rpl {scalar_t__ status; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; struct l2t_data* l2t; } ;
struct TYPE_2__ {int nud_state; } ;

/* Variables and functions */
 scalar_t__ CPL_ERR_NONE ; 
 unsigned int GET_TID (struct cpl_l2t_write_rpl const*) ; 
 unsigned int L2T_SIZE ; 
 scalar_t__ L2T_STATE_STALE ; 
 scalar_t__ L2T_STATE_SWITCHING ; 
 scalar_t__ L2T_STATE_VALID ; 
 int NUD_STALE ; 
 unsigned int SYNC_WR_F ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  send_pending (struct adapter*,struct l2t_entry*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void do_l2t_write_rpl(struct adapter *adap, const struct cpl_l2t_write_rpl *rpl)
{
	struct l2t_data *d = adap->l2t;
	unsigned int tid = GET_TID(rpl);
	unsigned int l2t_idx = tid % L2T_SIZE;

	if (unlikely(rpl->status != CPL_ERR_NONE)) {
		dev_err(adap->pdev_dev,
			"Unexpected L2T_WRITE_RPL status %u for entry %u\n",
			rpl->status, l2t_idx);
		return;
	}

	if (tid & SYNC_WR_F) {
		struct l2t_entry *e = &d->l2tab[l2t_idx - d->l2t_start];

		spin_lock(&e->lock);
		if (e->state != L2T_STATE_SWITCHING) {
			send_pending(adap, e);
			e->state = (e->neigh->nud_state & NUD_STALE) ?
					L2T_STATE_STALE : L2T_STATE_VALID;
		}
		spin_unlock(&e->lock);
	}
}