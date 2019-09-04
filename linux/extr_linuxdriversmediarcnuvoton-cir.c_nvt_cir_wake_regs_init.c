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
struct nvt_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CIR_WAKE_IRCON ; 
 int CIR_WAKE_IRCON_MODE0 ; 
 int CIR_WAKE_IRCON_R ; 
 int CIR_WAKE_IRCON_RXINV ; 
 int CIR_WAKE_IRCON_SAMPLE_PERIOD_SEL ; 
 int /*<<< orphan*/  CIR_WAKE_IRSTS ; 
 int /*<<< orphan*/  LOGICAL_DEV_CIR_WAKE ; 
 int /*<<< orphan*/  nvt_cir_wake_reg_write (struct nvt_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvt_enable_logical_dev (struct nvt_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nvt_cir_wake_regs_init(struct nvt_dev *nvt)
{
	nvt_enable_logical_dev(nvt, LOGICAL_DEV_CIR_WAKE);

	/*
	 * Disable RX, set specific carrier on = low, off = high,
	 * and sample period (currently 50us)
	 */
	nvt_cir_wake_reg_write(nvt, CIR_WAKE_IRCON_MODE0 |
			       CIR_WAKE_IRCON_R | CIR_WAKE_IRCON_RXINV |
			       CIR_WAKE_IRCON_SAMPLE_PERIOD_SEL,
			       CIR_WAKE_IRCON);

	/* clear any and all stray interrupts */
	nvt_cir_wake_reg_write(nvt, 0xff, CIR_WAKE_IRSTS);
}