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
struct stripe_head {size_t pd_idx; int /*<<< orphan*/  log_list; int /*<<< orphan*/  count; int /*<<< orphan*/  state; TYPE_1__* dev; int /*<<< orphan*/  ppl_page; struct ppl_io_unit* ppl_io; } ;
struct r5conf {struct ppl_conf* log_private; } ;
struct ppl_log {int /*<<< orphan*/  io_mutex; TYPE_2__* rdev; } ;
struct ppl_io_unit {int dummy; } ;
struct ppl_conf {int /*<<< orphan*/  no_mem_stripes_lock; int /*<<< orphan*/  no_mem_stripes; struct ppl_log* child_logs; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  Faulty ; 
 int /*<<< orphan*/  R5_Insync ; 
 int /*<<< orphan*/  R5_Wantwrite ; 
 int /*<<< orphan*/  STRIPE_DELAYED ; 
 int /*<<< orphan*/  STRIPE_LOG_TRAPPED ; 
 int /*<<< orphan*/  STRIPE_SYNCING ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ ppl_log_stripe (struct ppl_log*,struct stripe_head*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ppl_write_stripe(struct r5conf *conf, struct stripe_head *sh)
{
	struct ppl_conf *ppl_conf = conf->log_private;
	struct ppl_io_unit *io = sh->ppl_io;
	struct ppl_log *log;

	if (io || test_bit(STRIPE_SYNCING, &sh->state) || !sh->ppl_page ||
	    !test_bit(R5_Wantwrite, &sh->dev[sh->pd_idx].flags) ||
	    !test_bit(R5_Insync, &sh->dev[sh->pd_idx].flags)) {
		clear_bit(STRIPE_LOG_TRAPPED, &sh->state);
		return -EAGAIN;
	}

	log = &ppl_conf->child_logs[sh->pd_idx];

	mutex_lock(&log->io_mutex);

	if (!log->rdev || test_bit(Faulty, &log->rdev->flags)) {
		mutex_unlock(&log->io_mutex);
		return -EAGAIN;
	}

	set_bit(STRIPE_LOG_TRAPPED, &sh->state);
	clear_bit(STRIPE_DELAYED, &sh->state);
	atomic_inc(&sh->count);

	if (ppl_log_stripe(log, sh)) {
		spin_lock_irq(&ppl_conf->no_mem_stripes_lock);
		list_add_tail(&sh->log_list, &ppl_conf->no_mem_stripes);
		spin_unlock_irq(&ppl_conf->no_mem_stripes_lock);
	}

	mutex_unlock(&log->io_mutex);

	return 0;
}