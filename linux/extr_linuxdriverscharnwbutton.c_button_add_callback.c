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
struct TYPE_2__ {void (* callback ) () ;int count; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 TYPE_1__* button_callback_list ; 
 int callback_count ; 

int button_add_callback (void (*callback) (void), int count)
{
	int lp = 0;
	if (callback_count == 32) {
		return -ENOMEM;
	}
	if (!callback) {
		return -EINVAL;
	}
	callback_count++;
	for (; (button_callback_list [lp].callback); lp++);
	button_callback_list [lp].callback = callback;
	button_callback_list [lp].count = count;
	return 0;
}