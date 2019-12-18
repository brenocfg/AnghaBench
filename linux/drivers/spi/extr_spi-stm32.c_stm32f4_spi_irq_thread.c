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
struct stm32_spi {int dummy; } ;
struct spi_master {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  spi_finalize_current_transfer (struct spi_master*) ; 
 struct stm32_spi* spi_master_get_devdata (struct spi_master*) ; 
 int /*<<< orphan*/  stm32f4_spi_disable (struct stm32_spi*) ; 

__attribute__((used)) static irqreturn_t stm32f4_spi_irq_thread(int irq, void *dev_id)
{
	struct spi_master *master = dev_id;
	struct stm32_spi *spi = spi_master_get_devdata(master);

	spi_finalize_current_transfer(master);
	stm32f4_spi_disable(spi);

	return IRQ_HANDLED;
}