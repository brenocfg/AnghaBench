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
struct config_group {int dummy; } ;
struct cma_device {int dummy; } ;
struct cma_dev_group {struct config_group device_group; struct config_group ports_group; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 struct config_group* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  cma_deref_dev (struct cma_device*) ; 
 int /*<<< orphan*/  cma_device_group_type ; 
 struct cma_device* cma_enum_devices_by_ibdev (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  cma_ports_group_type ; 
 int /*<<< orphan*/  config_group_init_type_name (struct config_group*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  configfs_add_default_group (struct config_group*,struct config_group*) ; 
 int /*<<< orphan*/  filter_by_name ; 
 int /*<<< orphan*/  kfree (struct cma_dev_group*) ; 
 struct cma_dev_group* kzalloc (int,int /*<<< orphan*/ ) ; 
 int make_cma_ports (struct cma_dev_group*,struct cma_device*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static struct config_group *make_cma_dev(struct config_group *group,
					 const char *name)
{
	int err = -ENODEV;
	struct cma_device *cma_dev = cma_enum_devices_by_ibdev(filter_by_name,
							       (void *)name);
	struct cma_dev_group *cma_dev_group = NULL;

	if (!cma_dev)
		goto fail;

	cma_dev_group = kzalloc(sizeof(*cma_dev_group), GFP_KERNEL);

	if (!cma_dev_group) {
		err = -ENOMEM;
		goto fail;
	}

	strlcpy(cma_dev_group->name, name, sizeof(cma_dev_group->name));

	config_group_init_type_name(&cma_dev_group->ports_group, "ports",
				    &cma_ports_group_type);

	err = make_cma_ports(cma_dev_group, cma_dev);
	if (err)
		goto fail;

	config_group_init_type_name(&cma_dev_group->device_group, name,
				    &cma_device_group_type);
	configfs_add_default_group(&cma_dev_group->ports_group,
			&cma_dev_group->device_group);

	cma_deref_dev(cma_dev);
	return &cma_dev_group->device_group;

fail:
	if (cma_dev)
		cma_deref_dev(cma_dev);
	kfree(cma_dev_group);
	return ERR_PTR(err);
}