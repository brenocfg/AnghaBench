#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kprobe_opcode_t ;
struct TYPE_5__ {scalar_t__ flags; int /*<<< orphan*/ * addr; } ;
struct TYPE_6__ {TYPE_1__ kp; } ;

/* Variables and functions */
 int EINVAL ; 
 int call_test_func (long (*) (long,long),int) ; 
 scalar_t__ kretprobe_handler_called ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int register_kretprobe (TYPE_2__*) ; 
 scalar_t__ test_func_instance ; 
 TYPE_2__ the_kretprobe ; 
 int /*<<< orphan*/  unregister_kretprobe (TYPE_2__*) ; 

__attribute__((used)) static int test_kretprobe(long (*func)(long, long))
{
	int ret;

	the_kretprobe.kp.addr = (kprobe_opcode_t *)func;
	ret = register_kretprobe(&the_kretprobe);
	if (ret < 0) {
		pr_err("FAIL: register_kretprobe failed with %d\n", ret);
		return ret;
	}

	ret = call_test_func(func, true);

	unregister_kretprobe(&the_kretprobe);
	the_kretprobe.kp.flags = 0; /* Clear disable flag to allow reuse */

	if (!ret)
		return -EINVAL;
	if (kretprobe_handler_called != test_func_instance) {
		pr_err("FAIL: kretprobe handler not called\n");
		return -EINVAL;
	}
	if (!call_test_func(func, false))
		return -EINVAL;
	if (kretprobe_handler_called == test_func_instance) {
		pr_err("FAIL: kretprobe called after unregistering\n");
		return -EINVAL;
	}

	return 0;
}