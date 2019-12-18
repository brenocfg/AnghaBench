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
struct smt_entry {int refcnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  src_mac; int /*<<< orphan*/  pfvf; int /*<<< orphan*/  state; } ;
struct smt_data {int /*<<< orphan*/  lock; } ;
struct adapter {struct smt_data* smt; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  SMT_STATE_SWITCHING ; 
 struct smt_entry* find_or_alloc_smte (struct smt_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_smt_entry (struct adapter*,struct smt_entry*) ; 
 int /*<<< orphan*/  write_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct smt_entry *t4_smt_alloc_switching(struct adapter *adap, u16 pfvf,
						u8 *smac)
{
	struct smt_data *s = adap->smt;
	struct smt_entry *e;

	write_lock_bh(&s->lock);
	e = find_or_alloc_smte(s, smac);
	if (e) {
		spin_lock(&e->lock);
		if (!e->refcnt) {
			e->refcnt = 1;
			e->state = SMT_STATE_SWITCHING;
			e->pfvf = pfvf;
			memcpy(e->src_mac, smac, ETH_ALEN);
			write_smt_entry(adap, e);
		} else {
			++e->refcnt;
		}
		spin_unlock(&e->lock);
	}
	write_unlock_bh(&s->lock);
	return e;
}