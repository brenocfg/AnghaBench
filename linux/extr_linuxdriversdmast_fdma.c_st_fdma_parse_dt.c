#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct st_fdma_driverdata {char* name; int id; } ;
struct st_fdma_dev {int /*<<< orphan*/  nr_channels; int /*<<< orphan*/  fw_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FW_NAME_SIZE ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,int) ; 

__attribute__((used)) static int st_fdma_parse_dt(struct platform_device *pdev,
			const struct st_fdma_driverdata *drvdata,
			struct st_fdma_dev *fdev)
{
	snprintf(fdev->fw_name, FW_NAME_SIZE, "fdma_%s_%d.elf",
		drvdata->name, drvdata->id);

	return of_property_read_u32(pdev->dev.of_node, "dma-channels",
				    &fdev->nr_channels);
}