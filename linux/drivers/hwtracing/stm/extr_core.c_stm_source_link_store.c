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
struct stm_source_device {int dummy; } ;
struct stm_device {int /*<<< orphan*/  dev; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  pm_runtime_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ *) ; 
 struct stm_device* stm_find_device (char const*) ; 
 int /*<<< orphan*/  stm_put_device (struct stm_device*) ; 
 int stm_source_link_add (struct stm_source_device*,struct stm_device*) ; 
 int /*<<< orphan*/  stm_source_link_drop (struct stm_source_device*) ; 
 struct stm_source_device* to_stm_source_device (struct device*) ; 

__attribute__((used)) static ssize_t stm_source_link_store(struct device *dev,
				     struct device_attribute *attr,
				     const char *buf, size_t count)
{
	struct stm_source_device *src = to_stm_source_device(dev);
	struct stm_device *link;
	int err;

	stm_source_link_drop(src);

	link = stm_find_device(buf);
	if (!link)
		return -EINVAL;

	pm_runtime_get(&link->dev);

	err = stm_source_link_add(src, link);
	if (err) {
		pm_runtime_put_autosuspend(&link->dev);
		/* matches the stm_find_device() above */
		stm_put_device(link);
	}

	return err ? : count;
}