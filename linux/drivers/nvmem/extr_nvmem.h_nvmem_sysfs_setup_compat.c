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
struct nvmem_config {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 

__attribute__((used)) static inline int nvmem_sysfs_setup_compat(struct nvmem_device *nvmem,
				      const struct nvmem_config *config)
{
	return -ENOSYS;
}