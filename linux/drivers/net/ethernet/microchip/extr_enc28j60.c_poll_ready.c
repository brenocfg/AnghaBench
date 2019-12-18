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
struct enc28j60_net {TYPE_1__* spi; } ;
struct device {int dummy; } ;
struct TYPE_2__ {struct device dev; } ;

/* Variables and functions */
 int ETIMEDOUT ; 
 int /*<<< orphan*/  cpu_relax () ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (int) ; 
 scalar_t__ netif_msg_drv (struct enc28j60_net*) ; 
 int nolock_regb_read (struct enc28j60_net*,int) ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static int poll_ready(struct enc28j60_net *priv, u8 reg, u8 mask, u8 val)
{
	struct device *dev = &priv->spi->dev;
	unsigned long timeout = jiffies + msecs_to_jiffies(20);

	/* 20 msec timeout read */
	while ((nolock_regb_read(priv, reg) & mask) != val) {
		if (time_after(jiffies, timeout)) {
			if (netif_msg_drv(priv))
				dev_dbg(dev, "reg %02x ready timeout!\n", reg);
			return -ETIMEDOUT;
		}
		cpu_relax();
	}
	return 0;
}