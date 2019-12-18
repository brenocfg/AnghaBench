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
struct lan78xx_net {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ HZ ; 
 int /*<<< orphan*/  MII_ACC ; 
 int MII_ACC_MII_BUSY_ ; 
 unsigned long jiffies ; 
 int lan78xx_read_reg (struct lan78xx_net*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  time_after (unsigned long,scalar_t__) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int lan78xx_phy_wait_not_busy(struct lan78xx_net *dev)
{
	unsigned long start_time = jiffies;
	u32 val;
	int ret;

	do {
		ret = lan78xx_read_reg(dev, MII_ACC, &val);
		if (unlikely(ret < 0))
			return -EIO;

		if (!(val & MII_ACC_MII_BUSY_))
			return 0;
	} while (!time_after(jiffies, start_time + HZ));

	return -EIO;
}