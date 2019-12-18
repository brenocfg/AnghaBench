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

/* Variables and functions */
 int ZYNQ_QSPI_CONFIG_BDRATE_MASK ; 
 int ZYNQ_QSPI_CONFIG_CPHA_MASK ; 
 int ZYNQ_QSPI_CONFIG_CPOL_MASK ; 
 int ZYNQ_QSPI_CONFIG_FWIDTH_MASK ; 
 int ZYNQ_QSPI_CONFIG_IFMODE_MASK ; 
 int ZYNQ_QSPI_CONFIG_MANSRTEN_MASK ; 
 int ZYNQ_QSPI_CONFIG_MANSRT_MASK ; 
 int ZYNQ_QSPI_CONFIG_MSTREN_MASK ; 
 int /*<<< orphan*/  ZYNQ_QSPI_CONFIG_OFFSET ; 
 int ZYNQ_QSPI_CONFIG_SSFORCE_MASK ; 
 int ZYNQ_QSPI_ENABLE_ENABLE_MASK ; 
 int /*<<< orphan*/  ZYNQ_QSPI_ENABLE_OFFSET ; 
 int /*<<< orphan*/  ZYNQ_QSPI_IDIS_OFFSET ; 
 int ZYNQ_QSPI_IXR_ALL_MASK ; 
 int ZYNQ_QSPI_IXR_RXNEMTY_MASK ; 
 int /*<<< orphan*/  ZYNQ_QSPI_LINEAR_CFG_OFFSET ; 
 int /*<<< orphan*/  ZYNQ_QSPI_RXD_OFFSET ; 
 int ZYNQ_QSPI_RX_THRESHOLD ; 
 int /*<<< orphan*/  ZYNQ_QSPI_RX_THRESH_OFFSET ; 
 int /*<<< orphan*/  ZYNQ_QSPI_STATUS_OFFSET ; 
 int ZYNQ_QSPI_TX_THRESHOLD ; 
 int /*<<< orphan*/  ZYNQ_QSPI_TX_THRESH_OFFSET ; 
 int zynq_qspi_read (struct zynq_qspi*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynq_qspi_write (struct zynq_qspi*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void zynq_qspi_init_hw(struct zynq_qspi *xqspi)
{
	u32 config_reg;

	zynq_qspi_write(xqspi, ZYNQ_QSPI_ENABLE_OFFSET, 0);
	zynq_qspi_write(xqspi, ZYNQ_QSPI_IDIS_OFFSET, ZYNQ_QSPI_IXR_ALL_MASK);

	/* Disable linear mode as the boot loader may have used it */
	zynq_qspi_write(xqspi, ZYNQ_QSPI_LINEAR_CFG_OFFSET, 0);

	/* Clear the RX FIFO */
	while (zynq_qspi_read(xqspi, ZYNQ_QSPI_STATUS_OFFSET) &
			      ZYNQ_QSPI_IXR_RXNEMTY_MASK)
		zynq_qspi_read(xqspi, ZYNQ_QSPI_RXD_OFFSET);

	zynq_qspi_write(xqspi, ZYNQ_QSPI_STATUS_OFFSET, ZYNQ_QSPI_IXR_ALL_MASK);
	config_reg = zynq_qspi_read(xqspi, ZYNQ_QSPI_CONFIG_OFFSET);
	config_reg &= ~(ZYNQ_QSPI_CONFIG_MSTREN_MASK |
			ZYNQ_QSPI_CONFIG_CPOL_MASK |
			ZYNQ_QSPI_CONFIG_CPHA_MASK |
			ZYNQ_QSPI_CONFIG_BDRATE_MASK |
			ZYNQ_QSPI_CONFIG_SSFORCE_MASK |
			ZYNQ_QSPI_CONFIG_MANSRTEN_MASK |
			ZYNQ_QSPI_CONFIG_MANSRT_MASK);
	config_reg |= (ZYNQ_QSPI_CONFIG_MSTREN_MASK |
		       ZYNQ_QSPI_CONFIG_SSFORCE_MASK |
		       ZYNQ_QSPI_CONFIG_FWIDTH_MASK |
		       ZYNQ_QSPI_CONFIG_IFMODE_MASK);
	zynq_qspi_write(xqspi, ZYNQ_QSPI_CONFIG_OFFSET, config_reg);

	zynq_qspi_write(xqspi, ZYNQ_QSPI_RX_THRESH_OFFSET,
			ZYNQ_QSPI_RX_THRESHOLD);
	zynq_qspi_write(xqspi, ZYNQ_QSPI_TX_THRESH_OFFSET,
			ZYNQ_QSPI_TX_THRESHOLD);

	zynq_qspi_write(xqspi, ZYNQ_QSPI_ENABLE_OFFSET,
			ZYNQ_QSPI_ENABLE_ENABLE_MASK);
}