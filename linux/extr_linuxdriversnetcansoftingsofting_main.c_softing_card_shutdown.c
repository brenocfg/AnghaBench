#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int up; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {scalar_t__ requested; scalar_t__ nr; } ;
struct softing {TYPE_3__ fw; int /*<<< orphan*/  pdev; TYPE_2__* pdat; TYPE_1__ irq; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* reset ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* enable_irq ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct softing*) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  softing_set_reset_dpram (struct softing*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void softing_card_shutdown(struct softing *card)
{
	int fw_up = 0;

	if (mutex_lock_interruptible(&card->fw.lock))
		/* return -ERESTARTSYS */;
	fw_up = card->fw.up;
	card->fw.up = 0;

	if (card->irq.requested && card->irq.nr) {
		free_irq(card->irq.nr, card);
		card->irq.requested = 0;
	}
	if (fw_up) {
		if (card->pdat->enable_irq)
			card->pdat->enable_irq(card->pdev, 0);
		softing_set_reset_dpram(card);
		if (card->pdat->reset)
			card->pdat->reset(card->pdev, 1);
	}
	mutex_unlock(&card->fw.lock);
}