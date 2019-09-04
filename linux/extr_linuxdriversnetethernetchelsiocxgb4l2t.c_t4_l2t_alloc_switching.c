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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u16 ;
struct l2t_entry {int /*<<< orphan*/  lock; int /*<<< orphan*/  refcnt; int /*<<< orphan*/  dmac; int /*<<< orphan*/  lport; int /*<<< orphan*/  vlan; int /*<<< orphan*/  state; } ;
struct l2t_data {int /*<<< orphan*/  lock; } ;
struct adapter {struct l2t_data* l2t; } ;

/* Variables and functions */
 int /*<<< orphan*/  L2T_STATE_SWITCHING ; 
 int /*<<< orphan*/  _t4_l2e_free (struct l2t_entry*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct l2t_entry* find_or_alloc_l2e (struct l2t_data*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int write_l2e (struct adapter*,struct l2t_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

struct l2t_entry *t4_l2t_alloc_switching(struct adapter *adap, u16 vlan,
					 u8 port, u8 *eth_addr)
{
	struct l2t_data *d = adap->l2t;
	struct l2t_entry *e;
	int ret;

	write_lock_bh(&d->lock);
	e = find_or_alloc_l2e(d, vlan, port, eth_addr);
	if (e) {
		spin_lock(&e->lock);          /* avoid race with t4_l2t_free */
		if (!atomic_read(&e->refcnt)) {
			e->state = L2T_STATE_SWITCHING;
			e->vlan = vlan;
			e->lport = port;
			ether_addr_copy(e->dmac, eth_addr);
			atomic_set(&e->refcnt, 1);
			ret = write_l2e(adap, e, 0);
			if (ret < 0) {
				_t4_l2e_free(e);
				spin_unlock(&e->lock);
				write_unlock_bh(&d->lock);
				return NULL;
			}
		} else {
			atomic_inc(&e->refcnt);
		}

		spin_unlock(&e->lock);
	}
	write_unlock_bh(&d->lock);
	return e;
}