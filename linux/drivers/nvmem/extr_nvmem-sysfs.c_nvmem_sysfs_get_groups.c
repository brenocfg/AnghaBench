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
struct nvmem_device {scalar_t__ read_only; } ;
struct nvmem_config {scalar_t__ root_only; } ;
struct attribute_group {int dummy; } ;

/* Variables and functions */
 struct attribute_group const** nvmem_ro_dev_groups ; 
 struct attribute_group const** nvmem_ro_root_dev_groups ; 
 struct attribute_group const** nvmem_rw_dev_groups ; 
 struct attribute_group const** nvmem_rw_root_dev_groups ; 

const struct attribute_group **nvmem_sysfs_get_groups(
					struct nvmem_device *nvmem,
					const struct nvmem_config *config)
{
	if (config->root_only)
		return nvmem->read_only ?
			nvmem_ro_root_dev_groups :
			nvmem_rw_root_dev_groups;

	return nvmem->read_only ? nvmem_ro_dev_groups : nvmem_rw_dev_groups;
}