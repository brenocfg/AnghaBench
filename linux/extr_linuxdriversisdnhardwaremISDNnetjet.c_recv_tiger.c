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
typedef  int u8 ;
typedef  int u32 ;
struct TYPE_4__ {int size; } ;
struct tiger_hw {int last_is0; TYPE_3__* bc; TYPE_1__ recv; } ;
struct TYPE_5__ {int /*<<< orphan*/  Flags; } ;
struct TYPE_6__ {TYPE_2__ bch; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_ACTIVE ; 
 int NJ_IRQM0_WR_END ; 
 int NJ_IRQM0_WR_MASK ; 
 int /*<<< orphan*/  read_dma (TYPE_3__*,int,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
recv_tiger(struct tiger_hw *card, u8 irq_stat)
{
	u32 idx;
	int cnt = card->recv.size / 2;

	/* Note receive is via the WRITE DMA channel */
	card->last_is0 &= ~NJ_IRQM0_WR_MASK;
	card->last_is0 |= (irq_stat & NJ_IRQM0_WR_MASK);

	if (irq_stat & NJ_IRQM0_WR_END)
		idx = cnt - 1;
	else
		idx = card->recv.size - 1;

	if (test_bit(FLG_ACTIVE, &card->bc[0].bch.Flags))
		read_dma(&card->bc[0], idx, cnt);
	if (test_bit(FLG_ACTIVE, &card->bc[1].bch.Flags))
		read_dma(&card->bc[1], idx, cnt);
}