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
struct device {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int acpi_dma_controller_register (struct device*,struct dma_chan* (*) (struct acpi_dma_spec*,struct acpi_dma*),void*) ; 
 int /*<<< orphan*/  devm_acpi_dma_release ; 
 int /*<<< orphan*/  devres_add (struct device*,void*) ; 
 void* devres_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devres_free (void*) ; 

int devm_acpi_dma_controller_register(struct device *dev,
		struct dma_chan *(*acpi_dma_xlate)
		(struct acpi_dma_spec *, struct acpi_dma *),
		void *data)
{
	void *res;
	int ret;

	res = devres_alloc(devm_acpi_dma_release, 0, GFP_KERNEL);
	if (!res)
		return -ENOMEM;

	ret = acpi_dma_controller_register(dev, acpi_dma_xlate, data);
	if (ret) {
		devres_free(res);
		return ret;
	}
	devres_add(dev, res);
	return 0;
}