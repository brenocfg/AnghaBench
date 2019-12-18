#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct simplefb_platform_data {int /*<<< orphan*/  format; int /*<<< orphan*/  stride; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct simplefb_params {TYPE_1__* format; int /*<<< orphan*/  stride; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 struct simplefb_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 TYPE_1__* simplefb_formats ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int simplefb_parse_pd(struct platform_device *pdev,
			     struct simplefb_params *params)
{
	struct simplefb_platform_data *pd = dev_get_platdata(&pdev->dev);
	int i;

	params->width = pd->width;
	params->height = pd->height;
	params->stride = pd->stride;

	params->format = NULL;
	for (i = 0; i < ARRAY_SIZE(simplefb_formats); i++) {
		if (strcmp(pd->format, simplefb_formats[i].name))
			continue;

		params->format = &simplefb_formats[i];
		break;
	}

	if (!params->format) {
		dev_err(&pdev->dev, "Invalid format value\n");
		return -EINVAL;
	}

	return 0;
}