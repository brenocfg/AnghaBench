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
struct r5conf {unsigned long rmw_level; } ;
struct mddev {struct r5conf* private; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  xor_syndrome; } ;

/* Variables and functions */
 size_t EINVAL ; 
 size_t ENODEV ; 
 size_t PAGE_SIZE ; 
 unsigned long PARITY_DISABLE_RMW ; 
 unsigned long PARITY_ENABLE_RMW ; 
 unsigned long PARITY_PREFER_RMW ; 
 scalar_t__ kstrtoul (char const*,int,unsigned long*) ; 
 TYPE_1__ raid6_call ; 

__attribute__((used)) static ssize_t
raid5_store_rmw_level(struct mddev  *mddev, const char *page, size_t len)
{
	struct r5conf *conf = mddev->private;
	unsigned long new;

	if (!conf)
		return -ENODEV;

	if (len >= PAGE_SIZE)
		return -EINVAL;

	if (kstrtoul(page, 10, &new))
		return -EINVAL;

	if (new != PARITY_DISABLE_RMW && !raid6_call.xor_syndrome)
		return -EINVAL;

	if (new != PARITY_DISABLE_RMW &&
	    new != PARITY_ENABLE_RMW &&
	    new != PARITY_PREFER_RMW)
		return -EINVAL;

	conf->rmw_level = new;
	return len;
}