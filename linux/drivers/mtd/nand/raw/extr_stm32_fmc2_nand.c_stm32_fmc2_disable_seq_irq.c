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
 scalar_t__ FMC2_CSQIER ; 
 int /*<<< orphan*/  FMC2_CSQIER_TCIE ; 
 int /*<<< orphan*/  FMC2_IRQ_UNKNOWN ; 
 int /*<<< orphan*/  readl_relaxed (scalar_t__) ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void stm32_fmc2_disable_seq_irq(struct stm32_fmc2_nfc *fmc2)
{
	u32 csqier = readl_relaxed(fmc2->io_base + FMC2_CSQIER);

	csqier &= ~FMC2_CSQIER_TCIE;

	writel_relaxed(csqier, fmc2->io_base + FMC2_CSQIER);

	fmc2->irq_state = FMC2_IRQ_UNKNOWN;
}