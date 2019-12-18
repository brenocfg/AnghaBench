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
struct sky2_hw {struct net_device** dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B3_RI_CTRL ; 
 int /*<<< orphan*/  BMU_CLR_IRQ_PAR ; 
 int /*<<< orphan*/  BMU_CLR_IRQ_TCP ; 
 int /*<<< orphan*/  GMF_CLI_TX_PE ; 
 int /*<<< orphan*/  Q_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_CSR ; 
 int /*<<< orphan*/  RAM_BUFFER (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RI_CLR_RD_PERR ; 
 int /*<<< orphan*/  RI_CLR_WR_PERR ; 
 int /*<<< orphan*/  SK_REG (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TX_GMF_CTRL_T ; 
 int Y2_IS_PAR_MAC1 ; 
 int Y2_IS_PAR_RD1 ; 
 int Y2_IS_PAR_RX1 ; 
 int Y2_IS_PAR_WR1 ; 
 int Y2_IS_TCP_TXA1 ; 
 scalar_t__ net_ratelimit () ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_info (struct net_device*,char*,int) ; 
 int /*<<< orphan*/ * rxqaddr ; 
 int /*<<< orphan*/  sky2_write16 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * txqaddr ; 

__attribute__((used)) static void sky2_hw_error(struct sky2_hw *hw, unsigned port, u32 status)
{
	struct net_device *dev = hw->dev[port];

	if (net_ratelimit())
		netdev_info(dev, "hw error interrupt status 0x%x\n", status);

	if (status & Y2_IS_PAR_RD1) {
		if (net_ratelimit())
			netdev_err(dev, "ram data read parity error\n");
		/* Clear IRQ */
		sky2_write16(hw, RAM_BUFFER(port, B3_RI_CTRL), RI_CLR_RD_PERR);
	}

	if (status & Y2_IS_PAR_WR1) {
		if (net_ratelimit())
			netdev_err(dev, "ram data write parity error\n");

		sky2_write16(hw, RAM_BUFFER(port, B3_RI_CTRL), RI_CLR_WR_PERR);
	}

	if (status & Y2_IS_PAR_MAC1) {
		if (net_ratelimit())
			netdev_err(dev, "MAC parity error\n");
		sky2_write8(hw, SK_REG(port, TX_GMF_CTRL_T), GMF_CLI_TX_PE);
	}

	if (status & Y2_IS_PAR_RX1) {
		if (net_ratelimit())
			netdev_err(dev, "RX parity error\n");
		sky2_write32(hw, Q_ADDR(rxqaddr[port], Q_CSR), BMU_CLR_IRQ_PAR);
	}

	if (status & Y2_IS_TCP_TXA1) {
		if (net_ratelimit())
			netdev_err(dev, "TCP segmentation error\n");
		sky2_write32(hw, Q_ADDR(txqaddr[port], Q_CSR), BMU_CLR_IRQ_TCP);
	}
}