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
 int CIR_IRCON_RXEN ; 
 int CIR_IRCON_RXINV ; 
 int CIR_IRCON_SAMPLE_PERIOD_SEL ; 
 int CIR_IRCON_TXEN ; 
 int /*<<< orphan*/  CIR_IRSTS ; 
 int /*<<< orphan*/  LOGICAL_DEV_CIR ; 
 int /*<<< orphan*/  nvt_cir_reg_write (struct nvt_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvt_enable_logical_dev (struct nvt_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvt_set_cir_iren (struct nvt_dev*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void nvt_enable_cir(struct nvt_dev *nvt)
{
	unsigned long flags;

	/* enable the CIR logical device */
	nvt_enable_logical_dev(nvt, LOGICAL_DEV_CIR);

	spin_lock_irqsave(&nvt->lock, flags);

	/*
	 * Enable TX and RX, specify carrier on = low, off = high, and set
	 * sample period (currently 50us)
	 */
	nvt_cir_reg_write(nvt, CIR_IRCON_TXEN | CIR_IRCON_RXEN |
			  CIR_IRCON_RXINV | CIR_IRCON_SAMPLE_PERIOD_SEL,
			  CIR_IRCON);

	/* clear all pending interrupts */
	nvt_cir_reg_write(nvt, 0xff, CIR_IRSTS);

	/* enable interrupts */
	nvt_set_cir_iren(nvt);

	spin_unlock_irqrestore(&nvt->lock, flags);
}