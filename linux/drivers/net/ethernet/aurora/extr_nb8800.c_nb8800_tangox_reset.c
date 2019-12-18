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
struct net_device {int dummy; } ;
struct nb8800_priv {int /*<<< orphan*/  clk; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int MAX_MDC_CLOCK ; 
 int /*<<< orphan*/  NB8800_TANGOX_MDIO_CLKDIV ; 
 int /*<<< orphan*/  NB8800_TANGOX_RESET ; 
 int /*<<< orphan*/  clk_get_rate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nb8800_writeb (struct nb8800_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nb8800_writew (struct nb8800_priv*,int /*<<< orphan*/ ,int) ; 
 struct nb8800_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static int nb8800_tangox_reset(struct net_device *dev)
{
	struct nb8800_priv *priv = netdev_priv(dev);
	int clk_div;

	nb8800_writeb(priv, NB8800_TANGOX_RESET, 0);
	usleep_range(1000, 10000);
	nb8800_writeb(priv, NB8800_TANGOX_RESET, 1);

	wmb();		/* ensure reset is cleared before proceeding */

	clk_div = DIV_ROUND_UP(clk_get_rate(priv->clk), 2 * MAX_MDC_CLOCK);
	nb8800_writew(priv, NB8800_TANGOX_MDIO_CLKDIV, clk_div);

	return 0;
}