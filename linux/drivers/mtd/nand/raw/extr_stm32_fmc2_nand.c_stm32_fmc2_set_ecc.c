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
struct stm32_fmc2_nfc {scalar_t__ io_base; } ;

/* Variables and functions */
 scalar_t__ FMC2_PCR ; 
 int /*<<< orphan*/  FMC2_PCR_ECCEN ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void stm32_fmc2_set_ecc(struct stm32_fmc2_nfc *fmc2, bool enable)
{
	u32 pcr = readl(fmc2->io_base + FMC2_PCR);

	pcr &= ~FMC2_PCR_ECCEN;
	if (enable)
		pcr |= FMC2_PCR_ECCEN;
	writel(pcr, fmc2->io_base + FMC2_PCR);
}