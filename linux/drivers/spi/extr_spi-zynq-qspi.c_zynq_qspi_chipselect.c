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
struct zynq_qspi {int dummy; } ;
struct spi_device {int /*<<< orphan*/  chip_select; struct spi_controller* master; } ;
struct spi_controller {int dummy; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZYNQ_QSPI_CONFIG_OFFSET ; 
 int ZYNQ_QSPI_CONFIG_SSCTRL_MASK ; 
 int ZYNQ_QSPI_SS_SHIFT ; 
 struct zynq_qspi* spi_controller_get_devdata (struct spi_controller*) ; 
 int zynq_qspi_read (struct zynq_qspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynq_qspi_write (struct zynq_qspi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void zynq_qspi_chipselect(struct spi_device *spi, bool assert)
{
	struct spi_controller *ctrl = spi->master;
	struct zynq_qspi *xqspi = spi_controller_get_devdata(ctrl);
	u32 config_reg;

	config_reg = zynq_qspi_read(xqspi, ZYNQ_QSPI_CONFIG_OFFSET);
	if (assert) {
		/* Select the slave */
		config_reg &= ~ZYNQ_QSPI_CONFIG_SSCTRL_MASK;
		config_reg |= (((~(BIT(spi->chip_select))) <<
				ZYNQ_QSPI_SS_SHIFT) &
				ZYNQ_QSPI_CONFIG_SSCTRL_MASK);
	} else {
		config_reg |= ZYNQ_QSPI_CONFIG_SSCTRL_MASK;
	}

	zynq_qspi_write(xqspi, ZYNQ_QSPI_CONFIG_OFFSET, config_reg);
}