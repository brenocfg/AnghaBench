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
struct smt_entry {int /*<<< orphan*/  lock; int /*<<< orphan*/  state; } ;
struct smt_data {struct smt_entry* smtab; } ;
struct cpl_smt_write_rpl {scalar_t__ status; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; struct smt_data* smt; } ;

/* Variables and functions */
 scalar_t__ CPL_ERR_NONE ; 
 int /*<<< orphan*/  GET_TID (struct cpl_smt_write_rpl const*) ; 
 int /*<<< orphan*/  SMT_STATE_ERROR ; 
 unsigned int TID_TID_G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

void do_smt_write_rpl(struct adapter *adap, const struct cpl_smt_write_rpl *rpl)
{
	unsigned int smtidx = TID_TID_G(GET_TID(rpl));
	struct smt_data *s = adap->smt;

	if (unlikely(rpl->status != CPL_ERR_NONE)) {
		struct smt_entry *e = &s->smtab[smtidx];

		dev_err(adap->pdev_dev,
			"Unexpected SMT_WRITE_RPL status %u for entry %u\n",
			rpl->status, smtidx);
		spin_lock(&e->lock);
		e->state = SMT_STATE_ERROR;
		spin_unlock(&e->lock);
		return;
	}
}