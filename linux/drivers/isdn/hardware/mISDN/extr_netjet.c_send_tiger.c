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
typedef  int u8 ;
struct tiger_hw {int last_is0; TYPE_2__* bc; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/  Flags; } ;
struct TYPE_4__ {TYPE_1__ bch; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_ACTIVE ; 
 int NJ_IRQM0_RD_MASK ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  send_tiger_bc (struct tiger_hw*,TYPE_2__*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
send_tiger(struct tiger_hw *card, u8 irq_stat)
{
	int i;

	/* Note send is via the READ DMA channel */
	if ((irq_stat & card->last_is0) & NJ_IRQM0_RD_MASK) {
		pr_info("%s: tiger warn write double dma %x/%x\n",
			card->name, irq_stat, card->last_is0);
		return;
	} else {
		card->last_is0 &= ~NJ_IRQM0_RD_MASK;
		card->last_is0 |= (irq_stat & NJ_IRQM0_RD_MASK);
	}
	for (i = 0; i < 2; i++) {
		if (test_bit(FLG_ACTIVE, &card->bc[i].bch.Flags))
			send_tiger_bc(card, &card->bc[i]);
	}
}