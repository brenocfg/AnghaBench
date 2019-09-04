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
typedef  scalar_t__ u32 ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct device_node {int dummy; } ;
struct aemif_device {scalar_t__ cs_offset; scalar_t__ num_cs; struct aemif_cs_data* cs_data; } ;
struct aemif_cs_data {int asize; void* enable_ss; void* enable_ew; scalar_t__ wsetup; scalar_t__ wstrobe; scalar_t__ whold; scalar_t__ rsetup; scalar_t__ rstrobe; scalar_t__ rhold; scalar_t__ ta; scalar_t__ cs; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ NUM_CS ; 
 int /*<<< orphan*/  aemif_get_hw_params (struct platform_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 
 void* of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 
 struct aemif_device* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int of_aemif_parse_abus_config(struct platform_device *pdev,
				      struct device_node *np)
{
	struct aemif_device *aemif = platform_get_drvdata(pdev);
	struct aemif_cs_data *data;
	u32 cs;
	u32 val;

	if (of_property_read_u32(np, "ti,cs-chipselect", &cs)) {
		dev_dbg(&pdev->dev, "cs property is required");
		return -EINVAL;
	}

	if (cs - aemif->cs_offset >= NUM_CS || cs < aemif->cs_offset) {
		dev_dbg(&pdev->dev, "cs number is incorrect %d", cs);
		return -EINVAL;
	}

	if (aemif->num_cs >= NUM_CS) {
		dev_dbg(&pdev->dev, "cs count is more than %d", NUM_CS);
		return -EINVAL;
	}

	data = &aemif->cs_data[aemif->num_cs];
	data->cs = cs;

	/* read the current value in the hw register */
	aemif_get_hw_params(pdev, aemif->num_cs++);

	/* override the values from device node */
	if (!of_property_read_u32(np, "ti,cs-min-turnaround-ns", &val))
		data->ta = val;

	if (!of_property_read_u32(np, "ti,cs-read-hold-ns", &val))
		data->rhold = val;

	if (!of_property_read_u32(np, "ti,cs-read-strobe-ns", &val))
		data->rstrobe = val;

	if (!of_property_read_u32(np, "ti,cs-read-setup-ns", &val))
		data->rsetup = val;

	if (!of_property_read_u32(np, "ti,cs-write-hold-ns", &val))
		data->whold = val;

	if (!of_property_read_u32(np, "ti,cs-write-strobe-ns", &val))
		data->wstrobe = val;

	if (!of_property_read_u32(np, "ti,cs-write-setup-ns", &val))
		data->wsetup = val;

	if (!of_property_read_u32(np, "ti,cs-bus-width", &val))
		if (val == 16)
			data->asize = 1;
	data->enable_ew = of_property_read_bool(np, "ti,cs-extended-wait-mode");
	data->enable_ss = of_property_read_bool(np, "ti,cs-select-strobe-mode");
	return 0;
}