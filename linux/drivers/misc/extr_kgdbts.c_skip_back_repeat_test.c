#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int idx; TYPE_1__* tst; } ;
struct TYPE_3__ {int /*<<< orphan*/  get; } ;

/* Variables and functions */
 int /*<<< orphan*/  fill_get_buf (int /*<<< orphan*/ ) ; 
 int repeat_test ; 
 int simple_strtol (char*,int /*<<< orphan*/ *,int) ; 
 TYPE_2__ ts ; 
 int /*<<< orphan*/  v1printk (char*,int) ; 

__attribute__((used)) static void skip_back_repeat_test(char *arg)
{
	int go_back = simple_strtol(arg, NULL, 10);

	repeat_test--;
	if (repeat_test <= 0) {
		ts.idx++;
	} else {
		if (repeat_test % 100 == 0)
			v1printk("kgdbts:RUN ... %d remaining\n", repeat_test);

		ts.idx -= go_back;
	}
	fill_get_buf(ts.tst[ts.idx].get);
}