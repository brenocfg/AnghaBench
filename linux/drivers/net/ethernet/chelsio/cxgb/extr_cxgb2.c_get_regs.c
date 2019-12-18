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
struct net_device {struct adapter* ml_priv; } ;
struct ethtool_regs {int version; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_CSPI_INTR_ENABLE ; 
 int /*<<< orphan*/  A_CSPI_RX_AE_WM ; 
 int /*<<< orphan*/  A_ESPI_GOSTAT ; 
 int /*<<< orphan*/  A_ESPI_SCH_TOKEN0 ; 
 int /*<<< orphan*/  A_MC3_CFG ; 
 int /*<<< orphan*/  A_MC4_INT_CAUSE ; 
 int /*<<< orphan*/  A_MC5_CONFIG ; 
 int /*<<< orphan*/  A_MC5_MASK_WRITE_CMD ; 
 int /*<<< orphan*/  A_PL_CAUSE ; 
 int /*<<< orphan*/  A_PL_ENABLE ; 
 int /*<<< orphan*/  A_RAT_INTR_CAUSE ; 
 int /*<<< orphan*/  A_RAT_ROUTE_CONTROL ; 
 int /*<<< orphan*/  A_SG_RESPACCUTIMER ; 
 int /*<<< orphan*/  A_TPI_ADDR ; 
 int /*<<< orphan*/  A_TPI_PAR ; 
 int /*<<< orphan*/  A_TP_IN_CONFIG ; 
 int /*<<< orphan*/  A_TP_TX_DROP_COUNT ; 
 int /*<<< orphan*/  A_ULP_PIO_CTRL ; 
 int /*<<< orphan*/  A_ULP_ULIMIT ; 
 int /*<<< orphan*/  T2_REGMAP_SIZE ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reg_block_dump (struct adapter*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void get_regs(struct net_device *dev, struct ethtool_regs *regs,
		     void *buf)
{
	struct adapter *ap = dev->ml_priv;

	/*
	 * Version scheme: bits 0..9: chip version, bits 10..15: chip revision
	 */
	regs->version = 2;

	memset(buf, 0, T2_REGMAP_SIZE);
	reg_block_dump(ap, buf, 0, A_SG_RESPACCUTIMER);
	reg_block_dump(ap, buf, A_MC3_CFG, A_MC4_INT_CAUSE);
	reg_block_dump(ap, buf, A_TPI_ADDR, A_TPI_PAR);
	reg_block_dump(ap, buf, A_TP_IN_CONFIG, A_TP_TX_DROP_COUNT);
	reg_block_dump(ap, buf, A_RAT_ROUTE_CONTROL, A_RAT_INTR_CAUSE);
	reg_block_dump(ap, buf, A_CSPI_RX_AE_WM, A_CSPI_INTR_ENABLE);
	reg_block_dump(ap, buf, A_ESPI_SCH_TOKEN0, A_ESPI_GOSTAT);
	reg_block_dump(ap, buf, A_ULP_ULIMIT, A_ULP_PIO_CTRL);
	reg_block_dump(ap, buf, A_PL_ENABLE, A_PL_CAUSE);
	reg_block_dump(ap, buf, A_MC5_CONFIG, A_MC5_MASK_WRITE_CMD);
}