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
struct atmel_qspi {scalar_t__ regs; int /*<<< orphan*/  mr; } ;

/* Variables and functions */
 scalar_t__ QSPI_CR ; 
 int /*<<< orphan*/  QSPI_CR_QSPIEN ; 
 int /*<<< orphan*/  QSPI_CR_SWRST ; 
 scalar_t__ QSPI_MR ; 
 int /*<<< orphan*/  QSPI_MR_SMM ; 
 int /*<<< orphan*/  writel_relaxed (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void atmel_qspi_init(struct atmel_qspi *aq)
{
	/* Reset the QSPI controller */
	writel_relaxed(QSPI_CR_SWRST, aq->regs + QSPI_CR);

	/* Set the QSPI controller by default in Serial Memory Mode */
	writel_relaxed(QSPI_MR_SMM, aq->regs + QSPI_MR);
	aq->mr = QSPI_MR_SMM;

	/* Enable the QSPI controller */
	writel_relaxed(QSPI_CR_QSPIEN, aq->regs + QSPI_CR);
}