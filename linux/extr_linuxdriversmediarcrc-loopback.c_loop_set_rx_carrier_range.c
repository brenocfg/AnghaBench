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
struct rc_dev {struct loopback_dev* priv; } ;
struct loopback_dev {int rxcarriermin; int rxcarriermax; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dprintk (char*,int,int) ; 

__attribute__((used)) static int loop_set_rx_carrier_range(struct rc_dev *dev, u32 min, u32 max)
{
	struct loopback_dev *lodev = dev->priv;

	if (min < 1 || min > max) {
		dprintk("invalid rx carrier range %u to %u\n", min, max);
		return -EINVAL;
	}

	dprintk("setting rx carrier range %u to %u\n", min, max);
	lodev->rxcarriermin = min;
	lodev->rxcarriermax = max;
	return 0;
}