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
struct of_mmc_spi {int /*<<< orphan*/  detect_irq; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,void*) ; 
 struct of_mmc_spi* to_of_mmc_spi (struct device*) ; 

__attribute__((used)) static void of_mmc_spi_exit(struct device *dev, void *mmc)
{
	struct of_mmc_spi *oms = to_of_mmc_spi(dev);

	free_irq(oms->detect_irq, mmc);
}