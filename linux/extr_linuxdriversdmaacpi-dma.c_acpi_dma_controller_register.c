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
struct acpi_dma {struct dma_chan* (* acpi_dma_xlate ) (struct acpi_dma_spec*,struct acpi_dma*) ;int /*<<< orphan*/  dma_controllers; void* data; struct device* dev; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 struct acpi_device* ACPI_COMPANION (struct device*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  acpi_dma_list ; 
 int /*<<< orphan*/  acpi_dma_lock ; 
 int /*<<< orphan*/  acpi_dma_parse_csrt (struct acpi_device*,struct acpi_dma*) ; 
 struct acpi_dma* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int acpi_dma_controller_register(struct device *dev,
		struct dma_chan *(*acpi_dma_xlate)
		(struct acpi_dma_spec *, struct acpi_dma *),
		void *data)
{
	struct acpi_device *adev;
	struct acpi_dma	*adma;

	if (!dev || !acpi_dma_xlate)
		return -EINVAL;

	/* Check if the device was enumerated by ACPI */
	adev = ACPI_COMPANION(dev);
	if (!adev)
		return -EINVAL;

	adma = kzalloc(sizeof(*adma), GFP_KERNEL);
	if (!adma)
		return -ENOMEM;

	adma->dev = dev;
	adma->acpi_dma_xlate = acpi_dma_xlate;
	adma->data = data;

	acpi_dma_parse_csrt(adev, adma);

	/* Now queue acpi_dma controller structure in list */
	mutex_lock(&acpi_dma_lock);
	list_add_tail(&adma->dma_controllers, &acpi_dma_list);
	mutex_unlock(&acpi_dma_lock);

	return 0;
}