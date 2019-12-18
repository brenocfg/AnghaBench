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
struct ti_qspi {int mmap_enabled; int /*<<< orphan*/  ctrl_reg; scalar_t__ ctrl_base; } ;
struct spi_device {int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  MEM_CS_MASK ; 
 int /*<<< orphan*/  QSPI_SPI_SWITCH_REG ; 
 int /*<<< orphan*/  regmap_update_bits (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ti_qspi* spi_master_get_devdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_qspi_write (struct ti_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ti_qspi_disable_memory_map(struct spi_device *spi)
{
	struct ti_qspi  *qspi = spi_master_get_devdata(spi->master);

	ti_qspi_write(qspi, 0, QSPI_SPI_SWITCH_REG);
	if (qspi->ctrl_base)
		regmap_update_bits(qspi->ctrl_base, qspi->ctrl_reg,
				   MEM_CS_MASK, 0);
	qspi->mmap_enabled = false;
}