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
struct nvmem_device {int /*<<< orphan*/  refcnt; int /*<<< orphan*/  dev; int /*<<< orphan*/  owner; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct nvmem_device* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvmem_dev_name (struct nvmem_device*) ; 
 struct nvmem_device* nvmem_find (char const*) ; 
 int /*<<< orphan*/  nvmem_mutex ; 
 struct nvmem_device* of_nvmem_find (struct device_node*) ; 
 int /*<<< orphan*/  put_device (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct nvmem_device *__nvmem_device_get(struct device_node *np,
					       const char *nvmem_name)
{
	struct nvmem_device *nvmem = NULL;

	mutex_lock(&nvmem_mutex);
	nvmem = np ? of_nvmem_find(np) : nvmem_find(nvmem_name);
	mutex_unlock(&nvmem_mutex);
	if (!nvmem)
		return ERR_PTR(-EPROBE_DEFER);

	if (!try_module_get(nvmem->owner)) {
		dev_err(&nvmem->dev,
			"could not increase module refcount for cell %s\n",
			nvmem_dev_name(nvmem));

		put_device(&nvmem->dev);
		return ERR_PTR(-EINVAL);
	}

	kref_get(&nvmem->refcnt);

	return nvmem;
}