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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct hw_regs {scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */
 struct hw_regs* hw_regs_range ; 

__attribute__((used)) static int netdev_get_regs_len(struct net_device *dev)
{
	struct hw_regs *range = hw_regs_range;
	int regs_len = 0x10 * sizeof(u32);

	while (range->end > range->start) {
		regs_len += (range->end - range->start + 3) / 4 * 4;
		range++;
	}
	return regs_len;
}