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
struct ei_device {int /*<<< orphan*/  irqlock; int /*<<< orphan*/  dmaing; } ;

/* Variables and functions */
 int /*<<< orphan*/  netdev_err (struct net_device*,char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mcf8390_dmaing_err(const char *func, struct net_device *dev,
			       struct ei_device *ei_local)
{
	netdev_err(dev, "%s: DMAing conflict [DMAstat:%d][irqlock:%d]\n",
		func, ei_local->dmaing, ei_local->irqlock);
}