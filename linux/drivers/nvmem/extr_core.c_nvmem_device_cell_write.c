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
struct nvmem_cell {int /*<<< orphan*/  bytes; } ;

/* Variables and functions */
 int EINVAL ; 
 int nvmem_cell_info_to_nvmem_cell (struct nvmem_device*,struct nvmem_cell_info*,struct nvmem_cell*) ; 
 int nvmem_cell_write (struct nvmem_cell*,void*,int /*<<< orphan*/ ) ; 

int nvmem_device_cell_write(struct nvmem_device *nvmem,
			    struct nvmem_cell_info *info, void *buf)
{
	struct nvmem_cell cell;
	int rc;

	if (!nvmem)
		return -EINVAL;

	rc = nvmem_cell_info_to_nvmem_cell(nvmem, info, &cell);
	if (rc)
		return rc;

	return nvmem_cell_write(&cell, buf, cell.bytes);
}