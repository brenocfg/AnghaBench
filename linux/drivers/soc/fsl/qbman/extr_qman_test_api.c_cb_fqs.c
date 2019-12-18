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
union qm_mr_entry {scalar_t__ verb; } ;
typedef  scalar_t__ u8 ;
struct qman_portal {int dummy; } ;
struct qman_fq {int dummy; } ;

/* Variables and functions */
 scalar_t__ QM_MR_VERB_FQRN ; 
 scalar_t__ QM_MR_VERB_FQRNI ; 
 scalar_t__ QM_MR_VERB_TYPE_MASK ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  pr_crit (char*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int retire_complete ; 
 int /*<<< orphan*/  waitqueue ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cb_fqs(struct qman_portal *p, struct qman_fq *fq,
		   const union qm_mr_entry *msg)
{
	u8 verb = (msg->verb & QM_MR_VERB_TYPE_MASK);

	if ((verb != QM_MR_VERB_FQRN) && (verb != QM_MR_VERB_FQRNI)) {
		pr_crit("unexpected FQS message");
		WARN_ON(1);
		return;
	}
	pr_info("Retirement message received\n");
	retire_complete = 1;
	wake_up(&waitqueue);
}