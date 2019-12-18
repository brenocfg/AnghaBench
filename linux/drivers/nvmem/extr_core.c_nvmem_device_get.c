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
struct nvmem_device {int dummy; } ;
struct device {scalar_t__ of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPROBE_DEFER ; 
 int /*<<< orphan*/  IS_ERR (struct nvmem_device*) ; 
 int /*<<< orphan*/  PTR_ERR (struct nvmem_device*) ; 
 struct nvmem_device* __nvmem_device_get (int /*<<< orphan*/ *,char const*) ; 
 struct nvmem_device* of_nvmem_device_get (scalar_t__,char const*) ; 

struct nvmem_device *nvmem_device_get(struct device *dev, const char *dev_name)
{
	if (dev->of_node) { /* try dt first */
		struct nvmem_device *nvmem;

		nvmem = of_nvmem_device_get(dev->of_node, dev_name);

		if (!IS_ERR(nvmem) || PTR_ERR(nvmem) == -EPROBE_DEFER)
			return nvmem;

	}

	return __nvmem_device_get(NULL, dev_name);
}