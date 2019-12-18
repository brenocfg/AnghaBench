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
struct spi_master {int dummy; } ;
struct a3700_spi {int wait_mask; int /*<<< orphan*/  done; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  A3700_SPI_INT_MASK_REG ; 
 int /*<<< orphan*/  A3700_SPI_INT_STAT_REG ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct a3700_spi* spi_master_get_devdata (struct spi_master*) ; 
 int spireg_read (struct a3700_spi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spireg_write (struct a3700_spi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t a3700_spi_interrupt(int irq, void *dev_id)
{
	struct spi_master *master = dev_id;
	struct a3700_spi *a3700_spi;
	u32 cause;

	a3700_spi = spi_master_get_devdata(master);

	/* Get interrupt causes */
	cause = spireg_read(a3700_spi, A3700_SPI_INT_STAT_REG);

	if (!cause || !(a3700_spi->wait_mask & cause))
		return IRQ_NONE;

	/* mask and acknowledge the SPI interrupts */
	spireg_write(a3700_spi, A3700_SPI_INT_MASK_REG, 0);
	spireg_write(a3700_spi, A3700_SPI_INT_STAT_REG, cause);

	/* Wake up the transfer */
	complete(&a3700_spi->done);

	return IRQ_HANDLED;
}