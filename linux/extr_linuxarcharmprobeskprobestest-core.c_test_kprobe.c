#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kprobe_opcode_t ;
struct TYPE_4__ {scalar_t__ flags; int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int call_test_func (long (*) (long,long),int) ; 
 scalar_t__ post_handler_called ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 scalar_t__ pre_handler_called ; 
 int register_kprobe (TYPE_1__*) ; 
 scalar_t__ test_func_instance ; 
 TYPE_1__ the_kprobe ; 
 int /*<<< orphan*/  unregister_kprobe (TYPE_1__*) ; 

__attribute__((used)) static int test_kprobe(long (*func)(long, long))
{
	int ret;

	the_kprobe.addr = (kprobe_opcode_t *)func;
	ret = register_kprobe(&the_kprobe);
	if (ret < 0) {
		pr_err("FAIL: register_kprobe failed with %d\n", ret);
		return ret;
	}

	ret = call_test_func(func, true);

	unregister_kprobe(&the_kprobe);
	the_kprobe.flags = 0; /* Clear disable flag to allow reuse */

	if (!ret)
		return -EINVAL;
	if (pre_handler_called != test_func_instance) {
		pr_err("FAIL: kprobe pre_handler not called\n");
		return -EINVAL;
	}
	if (post_handler_called != test_func_instance) {
		pr_err("FAIL: kprobe post_handler not called\n");
		return -EINVAL;
	}
	if (!call_test_func(func, false))
		return -EINVAL;
	if (pre_handler_called == test_func_instance ||
				post_handler_called == test_func_instance) {
		pr_err("FAIL: probe called after unregistering\n");
		return -EINVAL;
	}

	return 0;
}