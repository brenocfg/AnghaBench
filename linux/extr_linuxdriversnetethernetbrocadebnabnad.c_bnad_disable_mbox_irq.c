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
struct bnad {int /*<<< orphan*/  run_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNAD_RF_MBOX_IRQ_DISABLED ; 
 int /*<<< orphan*/  BNAD_UPDATE_CTR (struct bnad*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_intr_disabled ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bnad_disable_mbox_irq(struct bnad *bnad)
{
	set_bit(BNAD_RF_MBOX_IRQ_DISABLED, &bnad->run_flags);

	BNAD_UPDATE_CTR(bnad, mbox_intr_disabled);
}