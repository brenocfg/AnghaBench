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
typedef  int /*<<< orphan*/  u_long ;
struct TYPE_4__ {int (* init ) (TYPE_2__*) ;} ;
struct tiger_hw {int irq; int /*<<< orphan*/  lock; int /*<<< orphan*/ * bc; TYPE_2__ isac; int /*<<< orphan*/  name; TYPE_1__* pdev; } ;
struct TYPE_3__ {int irq; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int /*<<< orphan*/  ISDN_P_NONE ; 
 int inittiger (struct tiger_hw*) ; 
 int /*<<< orphan*/  mode_tiger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nj_disable_hwirq (struct tiger_hw*) ; 
 int /*<<< orphan*/  nj_irq ; 
 int /*<<< orphan*/  nj_reset (struct tiger_hw*) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct tiger_hw*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*) ; 

__attribute__((used)) static int
nj_init_card(struct tiger_hw *card)
{
	u_long flags;
	int ret;

	spin_lock_irqsave(&card->lock, flags);
	nj_disable_hwirq(card);
	spin_unlock_irqrestore(&card->lock, flags);

	card->irq = card->pdev->irq;
	if (request_irq(card->irq, nj_irq, IRQF_SHARED, card->name, card)) {
		pr_info("%s: couldn't get interrupt %d\n",
			card->name, card->irq);
		card->irq = -1;
		return -EIO;
	}

	spin_lock_irqsave(&card->lock, flags);
	nj_reset(card);
	ret = card->isac.init(&card->isac);
	if (ret)
		goto error;
	ret = inittiger(card);
	if (ret)
		goto error;
	mode_tiger(&card->bc[0], ISDN_P_NONE);
	mode_tiger(&card->bc[1], ISDN_P_NONE);
error:
	spin_unlock_irqrestore(&card->lock, flags);
	return ret;
}