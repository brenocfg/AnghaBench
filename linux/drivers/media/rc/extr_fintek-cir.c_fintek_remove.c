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
struct pnp_dev {int dummy; } ;
struct fintek_dev {int /*<<< orphan*/  rdev; int /*<<< orphan*/  cir_port_len; int /*<<< orphan*/  cir_addr; int /*<<< orphan*/  cir_irq; int /*<<< orphan*/  fintek_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIR_STATUS ; 
 int /*<<< orphan*/  CIR_STATUS_IRQ_MASK ; 
 int /*<<< orphan*/  fintek_cir_reg_write (struct fintek_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fintek_disable_cir (struct fintek_dev*) ; 
 int /*<<< orphan*/  fintek_enable_wake (struct fintek_dev*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct fintek_dev*) ; 
 int /*<<< orphan*/  kfree (struct fintek_dev*) ; 
 struct fintek_dev* pnp_get_drvdata (struct pnp_dev*) ; 
 int /*<<< orphan*/  rc_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_region (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void fintek_remove(struct pnp_dev *pdev)
{
	struct fintek_dev *fintek = pnp_get_drvdata(pdev);
	unsigned long flags;

	spin_lock_irqsave(&fintek->fintek_lock, flags);
	/* disable CIR */
	fintek_disable_cir(fintek);
	fintek_cir_reg_write(fintek, CIR_STATUS_IRQ_MASK, CIR_STATUS);
	/* enable CIR Wake (for IR power-on) */
	fintek_enable_wake(fintek);
	spin_unlock_irqrestore(&fintek->fintek_lock, flags);

	/* free resources */
	free_irq(fintek->cir_irq, fintek);
	release_region(fintek->cir_addr, fintek->cir_port_len);

	rc_unregister_device(fintek->rdev);

	kfree(fintek);
}