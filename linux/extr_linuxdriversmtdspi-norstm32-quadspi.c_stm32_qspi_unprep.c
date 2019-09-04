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
struct stm32_qspi_flash {struct stm32_qspi* qspi; } ;
struct stm32_qspi {int /*<<< orphan*/  lock; } ;
struct spi_nor {struct stm32_qspi_flash* priv; } ;
typedef  enum spi_nor_ops { ____Placeholder_spi_nor_ops } spi_nor_ops ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void stm32_qspi_unprep(struct spi_nor *nor, enum spi_nor_ops ops)
{
	struct stm32_qspi_flash *flash = nor->priv;
	struct stm32_qspi *qspi = flash->qspi;

	mutex_unlock(&qspi->lock);
}