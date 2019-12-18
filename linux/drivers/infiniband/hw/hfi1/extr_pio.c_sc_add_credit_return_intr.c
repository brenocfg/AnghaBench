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
struct send_context {scalar_t__ credit_intr_count; int /*<<< orphan*/  credit_ctrl_lock; int /*<<< orphan*/  credit_ctrl; int /*<<< orphan*/  hw_context; int /*<<< orphan*/  dd; } ;

/* Variables and functions */
 int /*<<< orphan*/  CREDIT_CTRL ; 
 int /*<<< orphan*/  CREDIT_CTRL_CREDIT_INTR_SMASK ; 
 int /*<<< orphan*/  SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_kctxt_csr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void sc_add_credit_return_intr(struct send_context *sc)
{
	unsigned long flags;

	/* lock must surround both the count change and the CSR update */
	spin_lock_irqsave(&sc->credit_ctrl_lock, flags);
	if (sc->credit_intr_count == 0) {
		sc->credit_ctrl |= SC(CREDIT_CTRL_CREDIT_INTR_SMASK);
		write_kctxt_csr(sc->dd, sc->hw_context,
				SC(CREDIT_CTRL), sc->credit_ctrl);
	}
	sc->credit_intr_count++;
	spin_unlock_irqrestore(&sc->credit_ctrl_lock, flags);
}