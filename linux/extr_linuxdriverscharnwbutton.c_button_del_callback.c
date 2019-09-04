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
struct TYPE_2__ {void (* callback ) () ;scalar_t__ count; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_1__* button_callback_list ; 
 int /*<<< orphan*/  callback_count ; 

int button_del_callback (void (*callback) (void))
{
	int lp = 31;
	if (!callback) {
		return -EINVAL;
	}
	while (lp >= 0) {
		if ((button_callback_list [lp].callback) == callback) {
			button_callback_list [lp].callback = NULL;
			button_callback_list [lp].count = 0;
			callback_count--;
			return 0;
		}
		lp--;
	}
	return -EINVAL;
}