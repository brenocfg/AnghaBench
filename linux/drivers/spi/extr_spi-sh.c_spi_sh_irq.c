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
struct spi_sh_data {unsigned long cr1; int /*<<< orphan*/  wait; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SPI_SH_CR1 ; 
 int /*<<< orphan*/  SPI_SH_CR4 ; 
 unsigned long SPI_SH_RBE ; 
 unsigned long SPI_SH_RBF ; 
 unsigned long SPI_SH_TBE ; 
 unsigned long SPI_SH_TBF ; 
 int /*<<< orphan*/  spi_sh_clear_bit (struct spi_sh_data*,int,int /*<<< orphan*/ ) ; 
 unsigned long spi_sh_read (struct spi_sh_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t spi_sh_irq(int irq, void *_ss)
{
	struct spi_sh_data *ss = (struct spi_sh_data *)_ss;
	unsigned long cr1;

	cr1 = spi_sh_read(ss, SPI_SH_CR1);
	if (cr1 & SPI_SH_TBE)
		ss->cr1 |= SPI_SH_TBE;
	if (cr1 & SPI_SH_TBF)
		ss->cr1 |= SPI_SH_TBF;
	if (cr1 & SPI_SH_RBE)
		ss->cr1 |= SPI_SH_RBE;
	if (cr1 & SPI_SH_RBF)
		ss->cr1 |= SPI_SH_RBF;

	if (ss->cr1) {
		spi_sh_clear_bit(ss, ss->cr1, SPI_SH_CR4);
		wake_up(&ss->wait);
	}

	return IRQ_HANDLED;
}