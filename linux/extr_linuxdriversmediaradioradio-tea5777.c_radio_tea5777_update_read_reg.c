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
struct radio_tea5777 {int read_reg; int needs_write; TYPE_1__* ops; scalar_t__ write_before_read; } ;
struct TYPE_2__ {int (* read_reg ) (struct radio_tea5777*,int*) ;} ;

/* Variables and functions */
 int ERESTARTSYS ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int radio_tea5777_set_freq (struct radio_tea5777*) ; 
 scalar_t__ schedule_timeout_interruptible (int /*<<< orphan*/ ) ; 
 int stub1 (struct radio_tea5777*,int*) ; 

__attribute__((used)) static int radio_tea5777_update_read_reg(struct radio_tea5777 *tea, int wait)
{
	int res;

	if (tea->read_reg != -1)
		return 0;

	if (tea->write_before_read && tea->needs_write) {
		res = radio_tea5777_set_freq(tea);
		if (res)
			return res;
	}

	if (wait) {
		if (schedule_timeout_interruptible(msecs_to_jiffies(wait)))
			return -ERESTARTSYS;
	}

	res = tea->ops->read_reg(tea, &tea->read_reg);
	if (res)
		return res;

	tea->needs_write = true;
	return 0;
}