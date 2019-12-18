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
struct gasket_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline int
gasket_check_and_invoke_callback_nolock(struct gasket_dev *gasket_dev,
					int (*cb_function)(struct gasket_dev *))
{
	int ret = 0;

	if (cb_function)
		ret = cb_function(gasket_dev);
	return ret;
}