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
typedef  scalar_t__ u32 ;
struct atmel_qspi {int /*<<< orphan*/  clk_rate; int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (unsigned long,int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  QSPI_CR ; 
 scalar_t__ QSPI_CR_QSPIEN ; 
 scalar_t__ QSPI_CR_SWRST ; 
 int /*<<< orphan*/  QSPI_MR ; 
 scalar_t__ QSPI_MR_NBBITS (int) ; 
 scalar_t__ QSPI_MR_SSM ; 
 int /*<<< orphan*/  QSPI_SCR ; 
 scalar_t__ QSPI_SCR_SCBR (scalar_t__) ; 
 unsigned long clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qspi_writel (struct atmel_qspi*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int atmel_qspi_init(struct atmel_qspi *aq)
{
	unsigned long src_rate;
	u32 mr, scr, scbr;

	/* Reset the QSPI controller */
	qspi_writel(aq, QSPI_CR, QSPI_CR_SWRST);

	/* Set the QSPI controller in Serial Memory Mode */
	mr = QSPI_MR_NBBITS(8) | QSPI_MR_SSM;
	qspi_writel(aq, QSPI_MR, mr);

	src_rate = clk_get_rate(aq->clk);
	if (!src_rate)
		return -EINVAL;

	/* Compute the QSPI baudrate */
	scbr = DIV_ROUND_UP(src_rate, aq->clk_rate);
	if (scbr > 0)
		scbr--;
	scr = QSPI_SCR_SCBR(scbr);
	qspi_writel(aq, QSPI_SCR, scr);

	/* Enable the QSPI controller */
	qspi_writel(aq, QSPI_CR, QSPI_CR_QSPIEN);

	return 0;
}