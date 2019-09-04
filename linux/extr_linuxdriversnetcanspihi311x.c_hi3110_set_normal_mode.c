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
typedef  int u8 ;
struct spi_device {int dummy; } ;
struct TYPE_2__ {int ctrlmode; int /*<<< orphan*/  state; } ;
struct hi3110_priv {TYPE_1__ can; } ;

/* Variables and functions */
 int CAN_CTRLMODE_LISTENONLY ; 
 int CAN_CTRLMODE_LOOPBACK ; 
 int /*<<< orphan*/  CAN_STATE_ERROR_ACTIVE ; 
 int EBUSY ; 
 int HI3110_CTRL0_LOOPBACK_MODE ; 
 int HI3110_CTRL0_MODE_MASK ; 
 int HI3110_CTRL0_MONITOR_MODE ; 
 int HI3110_CTRL0_NORMAL_MODE ; 
 int HI3110_CTRL1_TXEN ; 
 int HI3110_INT_BUSERR ; 
 int HI3110_INT_RXFIFO ; 
 int HI3110_INT_TXCPLT ; 
 int /*<<< orphan*/  HI3110_OST_DELAY_MS ; 
 int /*<<< orphan*/  HI3110_READ_CTRL0 ; 
 int /*<<< orphan*/  HI3110_WRITE_CTRL0 ; 
 int /*<<< orphan*/  HI3110_WRITE_CTRL1 ; 
 int /*<<< orphan*/  HI3110_WRITE_INTE ; 
 int hi3110_read (struct spi_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hi3110_write (struct spi_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdelay (int /*<<< orphan*/ ) ; 
 struct hi3110_priv* spi_get_drvdata (struct spi_device*) ; 

__attribute__((used)) static int hi3110_set_normal_mode(struct spi_device *spi)
{
	struct hi3110_priv *priv = spi_get_drvdata(spi);
	u8 reg = 0;

	hi3110_write(spi, HI3110_WRITE_INTE, HI3110_INT_BUSERR |
		     HI3110_INT_RXFIFO | HI3110_INT_TXCPLT);

	/* Enable TX */
	hi3110_write(spi, HI3110_WRITE_CTRL1, HI3110_CTRL1_TXEN);

	if (priv->can.ctrlmode & CAN_CTRLMODE_LOOPBACK)
		reg = HI3110_CTRL0_LOOPBACK_MODE;
	else if (priv->can.ctrlmode & CAN_CTRLMODE_LISTENONLY)
		reg = HI3110_CTRL0_MONITOR_MODE;
	else
		reg = HI3110_CTRL0_NORMAL_MODE;

	hi3110_write(spi, HI3110_WRITE_CTRL0, reg);

	/* Wait for the device to enter the mode */
	mdelay(HI3110_OST_DELAY_MS);
	reg = hi3110_read(spi, HI3110_READ_CTRL0);
	if ((reg & HI3110_CTRL0_MODE_MASK) != reg)
		return -EBUSY;

	priv->can.state = CAN_STATE_ERROR_ACTIVE;
	return 0;
}