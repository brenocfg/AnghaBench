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
struct clk {int dummy; } ;

/* Variables and functions */
 long DIV_ROUND_UP (long,long) ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 long abs (long) ; 
 long clk_round_rate (struct clk*,long) ; 
 scalar_t__ clk_set_rate (struct clk*,long) ; 
 int /*<<< orphan*/  netdev_err (struct net_device*,char*) ; 
 int /*<<< orphan*/  netdev_warn (struct net_device*,char*,long) ; 

__attribute__((used)) static void macb_set_tx_clk(struct clk *clk, int speed, struct net_device *dev)
{
	long ferr, rate, rate_rounded;

	if (!clk)
		return;

	switch (speed) {
	case SPEED_10:
		rate = 2500000;
		break;
	case SPEED_100:
		rate = 25000000;
		break;
	case SPEED_1000:
		rate = 125000000;
		break;
	default:
		return;
	}

	rate_rounded = clk_round_rate(clk, rate);
	if (rate_rounded < 0)
		return;

	/* RGMII allows 50 ppm frequency error. Test and warn if this limit
	 * is not satisfied.
	 */
	ferr = abs(rate_rounded - rate);
	ferr = DIV_ROUND_UP(ferr, rate / 100000);
	if (ferr > 5)
		netdev_warn(dev, "unable to generate target frequency: %ld Hz\n",
			    rate);

	if (clk_set_rate(clk, rate_rounded))
		netdev_err(dev, "adjusting tx_clk failed.\n");
}