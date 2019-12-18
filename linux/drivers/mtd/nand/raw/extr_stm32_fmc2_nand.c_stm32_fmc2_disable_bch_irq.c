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
typedef  int /*<<< orphan*/  u32 ;
struct stm32_fmc2_nfc {int /*<<< orphan*/  irq_state; scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ FMC2_BCHIER ; 
 int /*<<< orphan*/  FMC2_BCHIER_DERIE ; 
 int /*<<< orphan*/  FMC2_BCHIER_EPBRIE ; 
 int /*<<< orphan*/  FMC2_IRQ_UNKNOWN ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void stm32_fmc2_disable_bch_irq(struct stm32_fmc2_nfc *fmc2)
{
	u32 bchier = readl_relaxed(fmc2->io_base + FMC2_BCHIER);

	bchier &= ~FMC2_BCHIER_DERIE;
	bchier &= ~FMC2_BCHIER_EPBRIE;

	writel_relaxed(bchier, fmc2->io_base + FMC2_BCHIER);

	fmc2->irq_state = FMC2_IRQ_UNKNOWN;
}