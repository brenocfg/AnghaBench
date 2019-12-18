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
typedef  int u16 ;
struct qcaspi {int /*<<< orphan*/  net_dev; } ;

/* Variables and functions */
 int SPI_INT_CPU_ON ; 
 int SPI_INT_PKT_AVLBL ; 
 int SPI_INT_RDBUF_ERR ; 
 int SPI_INT_WRBUF_ERR ; 
 int /*<<< orphan*/  SPI_REG_INTR_CAUSE ; 
 int /*<<< orphan*/  SPI_REG_INTR_ENABLE ; 
 int /*<<< orphan*/  netdev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  qcaspi_write_register (struct qcaspi*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr_verify ; 

__attribute__((used)) static void
end_spi_intr_handling(struct qcaspi *qca, u16 intr_cause)
{
	u16 intr_enable = (SPI_INT_CPU_ON |
			   SPI_INT_PKT_AVLBL |
			   SPI_INT_RDBUF_ERR |
			   SPI_INT_WRBUF_ERR);

	qcaspi_write_register(qca, SPI_REG_INTR_CAUSE, intr_cause, 0);
	qcaspi_write_register(qca, SPI_REG_INTR_ENABLE, intr_enable, wr_verify);
	netdev_dbg(qca->net_dev, "acking int: 0x%04x\n", intr_cause);
}