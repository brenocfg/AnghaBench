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
struct host1x_channel {scalar_t__ regs; } ;
struct host1x {scalar_t__ regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  enable_gather_filter (struct host1x*,struct host1x_channel*) ; 

__attribute__((used)) static int host1x_channel_init(struct host1x_channel *ch, struct host1x *dev,
			       unsigned int index)
{
#if HOST1X_HW < 6
	ch->regs = dev->regs + index * 0x4000;
#else
	ch->regs = dev->regs + index * 0x100;
#endif
	enable_gather_filter(dev, ch);
	return 0;
}