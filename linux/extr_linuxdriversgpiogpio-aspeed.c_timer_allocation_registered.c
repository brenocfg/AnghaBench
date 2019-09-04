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
struct aspeed_gpio {scalar_t__* offset_timer; } ;

/* Variables and functions */

__attribute__((used)) static inline bool timer_allocation_registered(struct aspeed_gpio *gpio,
		unsigned int offset)
{
	return gpio->offset_timer[offset] > 0;
}