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
struct nvmem_cell_info {int dummy; } ;
struct nvmem_cell {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int EINVAL ; 
 int __nvmem_cell_read (struct nvmem_device*,struct nvmem_cell*,void*,int*) ; 
 int nvmem_cell_info_to_nvmem_cell (struct nvmem_device*,struct nvmem_cell_info*,struct nvmem_cell*) ; 

ssize_t nvmem_device_cell_read(struct nvmem_device *nvmem,
			   struct nvmem_cell_info *info, void *buf)
{
	struct nvmem_cell cell;
	int rc;
	ssize_t len;

	if (!nvmem)
		return -EINVAL;

	rc = nvmem_cell_info_to_nvmem_cell(nvmem, info, &cell);
	if (rc)
		return rc;

	rc = __nvmem_cell_read(nvmem, &cell, buf, &len);
	if (rc)
		return rc;

	return len;
}