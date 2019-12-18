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

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct nvmem_cell* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ERR (struct nvmem_cell*) ; 
 int /*<<< orphan*/  devm_nvmem_cell_release ; 
 int /*<<< orphan*/  devres_add (struct device*,struct nvmem_cell**) ; 
 struct nvmem_cell** devres_alloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (struct nvmem_cell**) ; 
 struct nvmem_cell* nvmem_cell_get (struct device*,char const*) ; 

struct nvmem_cell *devm_nvmem_cell_get(struct device *dev, const char *id)
{
	struct nvmem_cell **ptr, *cell;

	ptr = devres_alloc(devm_nvmem_cell_release, sizeof(*ptr), GFP_KERNEL);
	if (!ptr)
		return ERR_PTR(-ENOMEM);

	cell = nvmem_cell_get(dev, id);
	if (!IS_ERR(cell)) {
		*ptr = cell;
		devres_add(dev, ptr);
	} else {
		devres_free(ptr);
	}

	return cell;
}