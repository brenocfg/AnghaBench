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
struct spi_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int ctrlmode; int /*<<< orphan*/  state; } ;
struct mcp251x_priv {TYPE_1__ can; } ;

/* Variables and functions */
 int /*<<< orphan*/  CANCTRL ; 
 int CANCTRL_REQOP_LISTEN_ONLY ; 
 int CANCTRL_REQOP_LOOPBACK ; 
 int CANCTRL_REQOP_MASK ; 
 int CANCTRL_REQOP_NORMAL ; 
 int /*<<< orphan*/  CANINTE ; 
 int CANINTE_ERRIE ; 
 int CANINTE_RX0IE ; 
 int CANINTE_RX1IE ; 
 int CANINTE_TX0IE ; 
 int CANINTE_TX1IE ; 
 int CANINTE_TX2IE ; 
 int /*<<< orphan*/  CANSTAT ; 
 int CAN_CTRLMODE_LISTENONLY ; 
 int CAN_CTRLMODE_LOOPBACK ; 
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 int EBUSY ; 
 unsigned long HZ ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 unsigned long jiffies ; 
 int mcp251x_read_reg (struct spi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcp251x_write_reg (struct spi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule () ; 
 struct mcp251x_priv* spi_get_drvdata (struct spi_device*) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int mcp251x_set_normal_mode(struct spi_device *spi)
{
	struct mcp251x_priv *priv = spi_get_drvdata(spi);
	unsigned long timeout;

	/* Enable interrupts */
	mcp251x_write_reg(spi, CANINTE,
			  CANINTE_ERRIE | CANINTE_TX2IE | CANINTE_TX1IE |
			  CANINTE_TX0IE | CANINTE_RX1IE | CANINTE_RX0IE);

	if (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK) {
		/* Put device into loopback mode */
		mcp251x_write_reg(spi, CANCTRL, CANCTRL_REQOP_LOOPBACK);
	} else if (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY) {
		/* Put device into listen-only mode */
		mcp251x_write_reg(spi, CANCTRL, CANCTRL_REQOP_LISTEN_ONLY);
	} else {
		/* Put device into normal mode */
		mcp251x_write_reg(spi, CANCTRL, CANCTRL_REQOP_NORMAL);

		/* Wait for the device to enter normal mode */
		timeout = jiffies + HZ;
		while (mcp251x_read_reg(spi, CANSTAT) & CANCTRL_REQOP_MASK) {
			schedule();
			if (time_after(jiffies, timeout)) {
				dev_err(&spi->dev, "MCP251x didn't enter in normal mode\n");
				return -EBUSY;
			}
		}
	}
	priv->can.state = CAN_STATE_ERROR_ACTIVE;
	return 0;
}