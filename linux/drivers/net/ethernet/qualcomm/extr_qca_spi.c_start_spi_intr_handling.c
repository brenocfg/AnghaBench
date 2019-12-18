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
typedef  scalar_t__ u16 ;
struct qcaspi {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPI_REG_INTR_CAUSE ; 
 int /*<<< orphan*/  SPI_REG_INTR_ENABLE ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  qcaspi_read_register (struct qcaspi*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  qcaspi_write_register (struct qcaspi*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr_verify ; 

__attribute__((used)) static void
start_spi_intr_handling(struct qcaspi *qca, u16 *intr_cause)
{
	*intr_cause = 0;

	qcaspi_write_register(qca, SPI_REG_INTR_ENABLE, 0, wr_verify);
	qcaspi_read_register(qca, SPI_REG_INTR_CAUSE, intr_cause);
	netdev_dbg(qca->net_dev, "interrupts: 0x%04x\n", *intr_cause);
}