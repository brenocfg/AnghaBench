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
struct nvmem_cell {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 char* ERR_CAST (struct nvmem_cell*) ; 
 scalar_t__ IS_ERR (struct nvmem_cell*) ; 
 struct nvmem_cell* nvmem_cell_get (struct device*,char const*) ; 
 int /*<<< orphan*/  nvmem_cell_put (struct nvmem_cell*) ; 
 char* nvmem_cell_read (struct nvmem_cell*,int /*<<< orphan*/ *) ; 

char *qfprom_read(struct device *dev, const char *cname)
{
	struct nvmem_cell *cell;
	ssize_t data;
	char *ret;

	cell = nvmem_cell_get(dev, cname);
	if (IS_ERR(cell))
		return ERR_CAST(cell);

	ret = nvmem_cell_read(cell, &data);
	nvmem_cell_put(cell);

	return ret;
}