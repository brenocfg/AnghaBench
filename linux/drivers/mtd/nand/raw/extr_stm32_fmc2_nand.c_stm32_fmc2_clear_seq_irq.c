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
struct stm32_fmc2_nfc {scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ FMC2_CSQICR ; 
 int /*<<< orphan*/  FMC2_CSQICR_CLEAR_IRQ ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void stm32_fmc2_clear_seq_irq(struct stm32_fmc2_nfc *fmc2)
{
	writel_relaxed(FMC2_CSQICR_CLEAR_IRQ, fmc2->io_base + FMC2_CSQICR);
}