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
struct vc_map {int init_er; int lacr; int max_er; int /*<<< orphan*/  class; struct rate_estimator* estimator; int /*<<< orphan*/  lock; } ;
struct rate_estimator {int /*<<< orphan*/  timer; } ;
struct idt77252_dev {int link_pcr; } ;
struct atm_vcc {int dummy; } ;
struct atm_qos {int /*<<< orphan*/  txtp; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCHED_UBR ; 
 int atm_pcr_goal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct rate_estimator* idt77252_init_est (struct vc_map*,int) ; 
 int idt77252_rate_logindex (struct idt77252_dev*,int) ; 
 int /*<<< orphan*/  kfree (struct rate_estimator*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int
idt77252_init_ubr(struct idt77252_dev *card, struct vc_map *vc,
		  struct atm_vcc *vcc, struct atm_qos *qos)
{
	struct rate_estimator *est = NULL;
	unsigned long flags;
	int tcr;

	spin_lock_irqsave(&vc->lock, flags);
	if (vc->estimator) {
		est = vc->estimator;
		vc->estimator = NULL;
	}
	spin_unlock_irqrestore(&vc->lock, flags);
	if (est) {
		del_timer_sync(&est->timer);
		kfree(est);
	}

	tcr = atm_pcr_goal(&qos->txtp);
	if (tcr == 0)
		tcr = card->link_pcr;

	vc->estimator = idt77252_init_est(vc, tcr);

	vc->class = SCHED_UBR;
	vc->init_er = idt77252_rate_logindex(card, tcr);
	vc->lacr = vc->init_er;
	if (tcr < 0)
		vc->max_er = vc->init_er;
	else
		vc->max_er = 0xff;

	return 0;
}