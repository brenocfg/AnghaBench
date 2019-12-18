#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  chip; } ;
struct adapter {int /*<<< orphan*/  pdev_dev; TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_PORT_INT_CAUSE_A ; 
 int PORT_REG (int,int /*<<< orphan*/ ) ; 
 int RXFIFO_PRTY_ERR_F ; 
 int T5_PORT_REG (int,int /*<<< orphan*/ ) ; 
 int TXFIFO_PRTY_ERR_F ; 
 int /*<<< orphan*/  XGMAC_PORT_INT_CAUSE_A ; 
 int /*<<< orphan*/  dev_alert (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ is_t4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t4_fatal_err (struct adapter*) ; 
 int t4_read_reg (struct adapter*,int) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int,int) ; 

__attribute__((used)) static void xgmac_intr_handler(struct adapter *adap, int port)
{
	u32 v, int_cause_reg;

	if (is_t4(adap->params.chip))
		int_cause_reg = PORT_REG(port, XGMAC_PORT_INT_CAUSE_A);
	else
		int_cause_reg = T5_PORT_REG(port, MAC_PORT_INT_CAUSE_A);

	v = t4_read_reg(adap, int_cause_reg);

	v &= TXFIFO_PRTY_ERR_F | RXFIFO_PRTY_ERR_F;
	if (!v)
		return;

	if (v & TXFIFO_PRTY_ERR_F)
		dev_alert(adap->pdev_dev, "XGMAC %d Tx FIFO parity error\n",
			  port);
	if (v & RXFIFO_PRTY_ERR_F)
		dev_alert(adap->pdev_dev, "XGMAC %d Rx FIFO parity error\n",
			  port);
	t4_write_reg(adap, PORT_REG(port, XGMAC_PORT_INT_CAUSE_A), v);
	t4_fatal_err(adap);
}