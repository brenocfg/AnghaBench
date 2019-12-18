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
typedef  int u32 ;
struct fsl_qspi {scalar_t__ iobase; } ;

/* Variables and functions */
 scalar_t__ QUADSPI_MCR ; 
 int QUADSPI_MCR_SWRSTHD_MASK ; 
 int QUADSPI_MCR_SWRSTSD_MASK ; 
 int qspi_readl (struct fsl_qspi*,scalar_t__) ; 
 int /*<<< orphan*/  qspi_writel (struct fsl_qspi*,int,scalar_t__) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void fsl_qspi_invalidate(struct fsl_qspi *q)
{
	u32 reg;

	reg = qspi_readl(q, q->iobase + QUADSPI_MCR);
	reg |= QUADSPI_MCR_SWRSTHD_MASK | QUADSPI_MCR_SWRSTSD_MASK;
	qspi_writel(q, reg, q->iobase + QUADSPI_MCR);

	/*
	 * The minimum delay : 1 AHB + 2 SFCK clocks.
	 * Delay 1 us is enough.
	 */
	udelay(1);

	reg &= ~(QUADSPI_MCR_SWRSTHD_MASK | QUADSPI_MCR_SWRSTSD_MASK);
	qspi_writel(q, reg, q->iobase + QUADSPI_MCR);
}