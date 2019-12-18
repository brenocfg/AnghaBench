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
typedef  int u8 ;
struct mxc_w1_device {scalar_t__ regs; } ;

/* Variables and functions */
 scalar_t__ MXC_W1_CONTROL ; 
 int MXC_W1_CONTROL_PST ; 
 int MXC_W1_CONTROL_RPP ; 
 unsigned long jiffies ; 
 int readb (scalar_t__) ; 
 scalar_t__ time_is_after_jiffies (unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 unsigned long usecs_to_jiffies (int) ; 
 int /*<<< orphan*/  writeb (int,scalar_t__) ; 

__attribute__((used)) static u8 mxc_w1_ds2_reset_bus(void *data)
{
	struct mxc_w1_device *dev = data;
	unsigned long timeout;

	writeb(MXC_W1_CONTROL_RPP, dev->regs + MXC_W1_CONTROL);

	/* Wait for reset sequence 511+512us, use 1500us for sure */
	timeout = jiffies + usecs_to_jiffies(1500);

	udelay(511 + 512);

	do {
		u8 ctrl = readb(dev->regs + MXC_W1_CONTROL);

		/* PST bit is valid after the RPP bit is self-cleared */
		if (!(ctrl & MXC_W1_CONTROL_RPP))
			return !(ctrl & MXC_W1_CONTROL_PST);
	} while (time_is_after_jiffies(timeout));

	return 1;
}