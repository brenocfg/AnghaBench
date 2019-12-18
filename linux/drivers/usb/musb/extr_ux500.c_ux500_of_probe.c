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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct musb_hdrc_platform_data {int /*<<< orphan*/  mode; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MUSB_HOST ; 
 int /*<<< orphan*/  MUSB_OTG ; 
 int /*<<< orphan*/  MUSB_PERIPHERAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct musb_hdrc_platform_data* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* of_get_property (struct device_node*,char*,int*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static struct musb_hdrc_platform_data *
ux500_of_probe(struct platform_device *pdev, struct device_node *np)
{
	struct musb_hdrc_platform_data *pdata;
	const char *mode;
	int strlen;

	pdata = devm_kzalloc(&pdev->dev, sizeof(*pdata), GFP_KERNEL);
	if (!pdata)
		return NULL;

	mode = of_get_property(np, "dr_mode", &strlen);
	if (!mode) {
		dev_err(&pdev->dev, "No 'dr_mode' property found\n");
		return NULL;
	}

	if (strlen > 0) {
		if (!strcmp(mode, "host"))
			pdata->mode = MUSB_HOST;
		if (!strcmp(mode, "otg"))
			pdata->mode = MUSB_OTG;
		if (!strcmp(mode, "peripheral"))
			pdata->mode = MUSB_PERIPHERAL;
	}

	return pdata;
}