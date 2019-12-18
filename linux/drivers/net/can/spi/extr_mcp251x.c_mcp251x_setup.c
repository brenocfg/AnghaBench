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
struct spi_device {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RXBCTRL (int) ; 
 int RXBCTRL_BUKT ; 
 int RXBCTRL_RXM0 ; 
 int RXBCTRL_RXM1 ; 
 int /*<<< orphan*/  mcp251x_do_set_bittiming (struct net_device*) ; 
 int /*<<< orphan*/  mcp251x_write_reg (struct spi_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mcp251x_setup(struct net_device *net, struct spi_device *spi)
{
	mcp251x_do_set_bittiming(net);

	mcp251x_write_reg(spi, RXBCTRL(0),
			  RXBCTRL_BUKT | RXBCTRL_RXM0 | RXBCTRL_RXM1);
	mcp251x_write_reg(spi, RXBCTRL(1),
			  RXBCTRL_RXM0 | RXBCTRL_RXM1);
	return 0;
}