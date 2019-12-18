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
struct zynq_qspi {int /*<<< orphan*/  pclk; int /*<<< orphan*/  refclk; } ;
struct spi_device {struct spi_controller* master; } ;
struct spi_controller {scalar_t__ busy; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  ZYNQ_QSPI_ENABLE_ENABLE_MASK ; 
 int /*<<< orphan*/  ZYNQ_QSPI_ENABLE_OFFSET ; 
 int /*<<< orphan*/  clk_enable (int /*<<< orphan*/ ) ; 
 struct zynq_qspi* spi_controller_get_devdata (struct spi_controller*) ; 
 int /*<<< orphan*/  zynq_qspi_write (struct zynq_qspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zynq_qspi_setup_op(struct spi_device *spi)
{
	struct spi_controller *ctrl = spi->master;
	struct zynq_qspi *qspi = spi_controller_get_devdata(ctrl);

	if (ctrl->busy)
		return -EBUSY;

	clk_enable(qspi->refclk);
	clk_enable(qspi->pclk);
	zynq_qspi_write(qspi, ZYNQ_QSPI_ENABLE_OFFSET,
			ZYNQ_QSPI_ENABLE_ENABLE_MASK);

	return 0;
}