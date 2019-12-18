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
struct device {scalar_t__ of_node; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  EPROBE_DEFER ; 
 struct nvmem_cell* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_ERR (struct nvmem_cell*) ; 
 int /*<<< orphan*/  PTR_ERR (struct nvmem_cell*) ; 
 struct nvmem_cell* nvmem_cell_get_from_lookup (struct device*,char const*) ; 
 struct nvmem_cell* of_nvmem_cell_get (scalar_t__,char const*) ; 

struct nvmem_cell *nvmem_cell_get(struct device *dev, const char *id)
{
	struct nvmem_cell *cell;

	if (dev->of_node) { /* try dt first */
		cell = of_nvmem_cell_get(dev->of_node, id);
		if (!IS_ERR(cell) || PTR_ERR(cell) == -EPROBE_DEFER)
			return cell;
	}

	/* NULL cell id only allowed for device tree; invalid otherwise */
	if (!id)
		return ERR_PTR(-EINVAL);

	return nvmem_cell_get_from_lookup(dev, id);
}