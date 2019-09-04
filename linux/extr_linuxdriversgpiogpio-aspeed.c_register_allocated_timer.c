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
struct aspeed_gpio {unsigned int* offset_timer; scalar_t__* timer_users; } ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ UINT_MAX ; 
 scalar_t__ WARN (int,char*,...) ; 

__attribute__((used)) static int register_allocated_timer(struct aspeed_gpio *gpio,
		unsigned int offset, unsigned int timer)
{
	if (WARN(gpio->offset_timer[offset] != 0,
				"Offset %d already allocated timer %d\n",
				offset, gpio->offset_timer[offset]))
		return -EINVAL;

	if (WARN(gpio->timer_users[timer] == UINT_MAX,
				"Timer user count would overflow\n"))
		return -EPERM;

	gpio->offset_timer[offset] = timer;
	gpio->timer_users[timer]++;

	return 0;
}