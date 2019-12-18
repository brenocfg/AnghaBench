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
struct stm_device {int /*<<< orphan*/  owner; } ;
struct device {int dummy; } ;

/* Variables and functions */
 struct device* class_find_device_by_name (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  put_device (struct device*) ; 
 int /*<<< orphan*/  stm_class ; 
 int /*<<< orphan*/  stm_core_up ; 
 struct stm_device* to_stm_device (struct device*) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

struct stm_device *stm_find_device(const char *buf)
{
	struct stm_device *stm;
	struct device *dev;

	if (!stm_core_up)
		return NULL;

	dev = class_find_device_by_name(&stm_class, buf);
	if (!dev)
		return NULL;

	stm = to_stm_device(dev);
	if (!try_module_get(stm->owner)) {
		/* matches class_find_device() above */
		put_device(dev);
		return NULL;
	}

	return stm;
}