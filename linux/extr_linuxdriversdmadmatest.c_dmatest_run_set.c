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
struct kernel_param {int dummy; } ;
struct dmatest_info {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ dmatest_run ; 
 scalar_t__ is_threaded_test_run (struct dmatest_info*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int param_set_bool (char const*,struct kernel_param const*) ; 
 int /*<<< orphan*/  restart_threaded_test (struct dmatest_info*,scalar_t__) ; 
 struct dmatest_info test_info ; 

__attribute__((used)) static int dmatest_run_set(const char *val, const struct kernel_param *kp)
{
	struct dmatest_info *info = &test_info;
	int ret;

	mutex_lock(&info->lock);
	ret = param_set_bool(val, kp);
	if (ret) {
		mutex_unlock(&info->lock);
		return ret;
	}

	if (is_threaded_test_run(info))
		ret = -EBUSY;
	else if (dmatest_run)
		restart_threaded_test(info, dmatest_run);

	mutex_unlock(&info->lock);

	return ret;
}