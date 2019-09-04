#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct rsq_entry {scalar_t__ word_4; } ;
struct TYPE_2__ {struct rsq_entry* base; struct rsq_entry* next; struct rsq_entry* last; } ;
struct idt77252_dev {TYPE_1__ rsq; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXPRINTK (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SAR_REG_RSQH ; 
 int SAR_RSQE_VALID ; 
 int /*<<< orphan*/  dequeue_rx (struct idt77252_dev*,struct rsq_entry*) ; 
 int le32_to_cpu (scalar_t__) ; 
 int /*<<< orphan*/  writel (unsigned long,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
idt77252_rx(struct idt77252_dev *card)
{
	struct rsq_entry *rsqe;

	if (card->rsq.next == card->rsq.last)
		rsqe = card->rsq.base;
	else
		rsqe = card->rsq.next + 1;

	if (!(le32_to_cpu(rsqe->word_4) & SAR_RSQE_VALID)) {
		RXPRINTK("%s: no entry in RSQ.\n", card->name);
		return;
	}

	do {
		dequeue_rx(card, rsqe);
		rsqe->word_4 = 0;
		card->rsq.next = rsqe;
		if (card->rsq.next == card->rsq.last)
			rsqe = card->rsq.base;
		else
			rsqe = card->rsq.next + 1;
	} while (le32_to_cpu(rsqe->word_4) & SAR_RSQE_VALID);

	writel((unsigned long) card->rsq.next - (unsigned long) card->rsq.base,
	       SAR_REG_RSQH);
}