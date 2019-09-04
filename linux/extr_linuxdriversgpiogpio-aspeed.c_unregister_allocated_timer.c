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
struct aspeed_gpio {size_t* offset_timer; scalar_t__* timer_users; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ WARN (int,char*,unsigned int) ; 

__attribute__((used)) static int unregister_allocated_timer(struct aspeed_gpio *gpio,
		unsigned int offset)
{
	if (WARN(gpio->offset_timer[offset] == 0,
				"No timer allocated to offset %d\n", offset))
		return -EINVAL;

	if (WARN(gpio->timer_users[gpio->offset_timer[offset]] == 0,
				"No users recorded for timer %d\n",
				gpio->offset_timer[offset]))
		return -EINVAL;

	gpio->timer_users[gpio->offset_timer[offset]]--;
	gpio->offset_timer[offset] = 0;

	return 0;
}