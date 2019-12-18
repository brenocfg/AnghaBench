#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  product; int /*<<< orphan*/  vendor; } ;
struct TYPE_7__ {int /*<<< orphan*/ * type; int /*<<< orphan*/ * bus; struct device* parent; } ;
struct ulpi {TYPE_1__ id; TYPE_2__ dev; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COMPANION (struct device*) ; 
 int /*<<< orphan*/  ACPI_COMPANION_SET (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 int /*<<< orphan*/  dev_set_name (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 int device_register (TYPE_2__*) ; 
 int /*<<< orphan*/  ulpi_bus ; 
 int /*<<< orphan*/  ulpi_dev_type ; 
 int ulpi_of_register (struct ulpi*) ; 
 int ulpi_read_id (struct ulpi*) ; 

__attribute__((used)) static int ulpi_register(struct device *dev, struct ulpi *ulpi)
{
	int ret;

	ulpi->dev.parent = dev; /* needed early for ops */
	ulpi->dev.bus = &ulpi_bus;
	ulpi->dev.type = &ulpi_dev_type;
	dev_set_name(&ulpi->dev, "%s.ulpi", dev_name(dev));

	ACPI_COMPANION_SET(&ulpi->dev, ACPI_COMPANION(dev));

	ret = ulpi_of_register(ulpi);
	if (ret)
		return ret;

	ret = ulpi_read_id(ulpi);
	if (ret)
		return ret;

	ret = device_register(&ulpi->dev);
	if (ret)
		return ret;

	dev_dbg(&ulpi->dev, "registered ULPI PHY: vendor %04x, product %04x\n",
		ulpi->id.vendor, ulpi->id.product);

	return 0;
}