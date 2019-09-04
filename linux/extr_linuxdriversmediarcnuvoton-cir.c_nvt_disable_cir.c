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
struct nvt_dev {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIR_IRCON ; 
 int /*<<< orphan*/  CIR_IREN ; 
 int /*<<< orphan*/  CIR_IRSTS ; 
 int /*<<< orphan*/  LOGICAL_DEV_CIR ; 
 int /*<<< orphan*/  nvt_cir_reg_write (struct nvt_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvt_clear_cir_fifo (struct nvt_dev*) ; 
 int /*<<< orphan*/  nvt_clear_tx_fifo (struct nvt_dev*) ; 
 int /*<<< orphan*/  nvt_disable_logical_dev (struct nvt_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void nvt_disable_cir(struct nvt_dev *nvt)
{
	unsigned long flags;

	spin_lock_irqsave(&nvt->lock, flags);

	/* disable CIR interrupts */
	nvt_cir_reg_write(nvt, 0, CIR_IREN);

	/* clear any and all pending interrupts */
	nvt_cir_reg_write(nvt, 0xff, CIR_IRSTS);

	/* clear all function enable flags */
	nvt_cir_reg_write(nvt, 0, CIR_IRCON);

	/* clear hardware rx and tx fifos */
	nvt_clear_cir_fifo(nvt);
	nvt_clear_tx_fifo(nvt);

	spin_unlock_irqrestore(&nvt->lock, flags);

	/* disable the CIR logical device */
	nvt_disable_logical_dev(nvt, LOGICAL_DEV_CIR);
}