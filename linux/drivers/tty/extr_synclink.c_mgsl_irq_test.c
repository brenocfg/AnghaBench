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
struct mgsl_struct {int irq_occurred; int /*<<< orphan*/  irq_spinlock; } ;

/* Variables and functions */
 int BIT12 ; 
 int BIT13 ; 
 int /*<<< orphan*/  IO_PIN ; 
 int /*<<< orphan*/  MISCSTATUS_TXC_LATCHED ; 
 int /*<<< orphan*/  PCR ; 
 scalar_t__ SICR_TXC_ACTIVE ; 
 scalar_t__ SICR_TXC_INACTIVE ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  usc_ClearIrqPendingBits (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_EnableInterrupts (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_EnableMasterIrqBit (struct mgsl_struct*) ; 
 int /*<<< orphan*/  usc_EnableStatusIrqs (struct mgsl_struct*,scalar_t__) ; 
 int usc_InReg (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_OutReg (struct mgsl_struct*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  usc_UnlatchIostatusBits (struct mgsl_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usc_reset (struct mgsl_struct*) ; 

__attribute__((used)) static bool mgsl_irq_test( struct mgsl_struct *info )
{
	unsigned long EndTime;
	unsigned long flags;

	spin_lock_irqsave(&info->irq_spinlock,flags);
	usc_reset(info);

	/*
	 * Setup 16C32 to interrupt on TxC pin (14MHz clock) transition. 
	 * The ISR sets irq_occurred to true.
	 */

	info->irq_occurred = false;

	/* Enable INTEN gate for ISA adapter (Port 6, Bit12) */
	/* Enable INTEN (Port 6, Bit12) */
	/* This connects the IRQ request signal to the ISA bus */
	/* on the ISA adapter. This has no effect for the PCI adapter */
	usc_OutReg( info, PCR, (unsigned short)((usc_InReg(info, PCR) | BIT13) & ~BIT12) );

	usc_EnableMasterIrqBit(info);
	usc_EnableInterrupts(info, IO_PIN);
	usc_ClearIrqPendingBits(info, IO_PIN);
	
	usc_UnlatchIostatusBits(info, MISCSTATUS_TXC_LATCHED);
	usc_EnableStatusIrqs(info, SICR_TXC_ACTIVE + SICR_TXC_INACTIVE);

	spin_unlock_irqrestore(&info->irq_spinlock,flags);

	EndTime=100;
	while( EndTime-- && !info->irq_occurred ) {
		msleep_interruptible(10);
	}
	
	spin_lock_irqsave(&info->irq_spinlock,flags);
	usc_reset(info);
	spin_unlock_irqrestore(&info->irq_spinlock,flags);
	
	return info->irq_occurred;

}