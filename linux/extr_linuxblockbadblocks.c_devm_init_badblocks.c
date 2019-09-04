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
struct device {int dummy; } ;
struct badblocks {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int __badblocks_init (struct device*,struct badblocks*,int) ; 

int devm_init_badblocks(struct device *dev, struct badblocks *bb)
{
	if (!bb)
		return -EINVAL;
	return __badblocks_init(dev, bb, 1);
}