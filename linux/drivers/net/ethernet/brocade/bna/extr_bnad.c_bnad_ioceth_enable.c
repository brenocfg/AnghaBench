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
struct TYPE_4__ {int ioc_comp_status; int /*<<< orphan*/  ioc_comp; } ;
struct TYPE_3__ {int /*<<< orphan*/  ioceth; } ;
struct bnad {TYPE_2__ bnad_completions; int /*<<< orphan*/  bna_lock; TYPE_1__ bna; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNAD_IOCETH_TIMEOUT ; 
 int BNA_CB_WAITING ; 
 int /*<<< orphan*/  bna_ioceth_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnad_ioceth_enable(struct bnad *bnad)
{
	int err = 0;
	unsigned long flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	init_completion(&bnad->bnad_completions.ioc_comp);
	bnad->bnad_completions.ioc_comp_status = BNA_CB_WAITING;
	bna_ioceth_enable(&bnad->bna.ioceth);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	wait_for_completion_timeout(&bnad->bnad_completions.ioc_comp,
		msecs_to_jiffies(BNAD_IOCETH_TIMEOUT));

	err = bnad->bnad_completions.ioc_comp_status;

	return err;
}