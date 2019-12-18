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
struct sky2_port {size_t port; int /*<<< orphan*/  netdev; struct sky2_hw* hw; } ;
struct sky2_hw {int dummy; } ;

/* Variables and functions */
 int BMU_FIFO_RST ; 
 int BMU_RST_SET ; 
 int /*<<< orphan*/  PREF_UNIT_CTRL ; 
 int PREF_UNIT_RST_SET ; 
 int /*<<< orphan*/  Q_ADDR (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Q_CSR ; 
 int /*<<< orphan*/  Q_RL ; 
 int /*<<< orphan*/  Q_RSL ; 
 int /*<<< orphan*/  RB_ADDR (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RB_CTRL ; 
 int /*<<< orphan*/  RB_DIS_OP_MD ; 
 int /*<<< orphan*/  Y2_QADDR (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netdev_warn (int /*<<< orphan*/ ,char*) ; 
 unsigned int* rxqaddr ; 
 scalar_t__ sky2_read8 (struct sky2_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sky2_write32 (struct sky2_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sky2_write8 (struct sky2_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sky2_rx_stop(struct sky2_port *sky2)
{
	struct sky2_hw *hw = sky2->hw;
	unsigned rxq = rxqaddr[sky2->port];
	int i;

	/* disable the RAM Buffer receive queue */
	sky2_write8(hw, RB_ADDR(rxq, RB_CTRL), RB_DIS_OP_MD);

	for (i = 0; i < 0xffff; i++)
		if (sky2_read8(hw, RB_ADDR(rxq, Q_RSL))
		    == sky2_read8(hw, RB_ADDR(rxq, Q_RL)))
			goto stopped;

	netdev_warn(sky2->netdev, "receiver stop failed\n");
stopped:
	sky2_write32(hw, Q_ADDR(rxq, Q_CSR), BMU_RST_SET | BMU_FIFO_RST);

	/* reset the Rx prefetch unit */
	sky2_write32(hw, Y2_QADDR(rxq, PREF_UNIT_CTRL), PREF_UNIT_RST_SET);
}