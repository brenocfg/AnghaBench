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
struct TYPE_2__ {int count; int /*<<< orphan*/  (* callback ) () ;} ;

/* Variables and functions */
 TYPE_1__* button_callback_list ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void button_consume_callbacks (int bpcount)
{
	int lp = 0;
	for (; lp <= 31; lp++) {
		if ((button_callback_list [lp].count) == bpcount) {
			if (button_callback_list [lp].callback) {
				button_callback_list[lp].callback();
			}
		}
	}
}