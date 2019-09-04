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
struct resource {int dummy; } ;
struct TYPE_3__ {char* platform_data; } ;
struct platform_device {int /*<<< orphan*/  id; TYPE_1__ dev; } ;
struct of_device_id {int /*<<< orphan*/  data; } ;
struct config_registers {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 int /*<<< orphan*/  buffer_icap_config ; 
 int /*<<< orphan*/  hwicap_of_match ; 
 int hwicap_of_probe (struct platform_device*,int /*<<< orphan*/ ) ; 
 int hwicap_setup (TYPE_1__*,int /*<<< orphan*/ ,struct resource*,int /*<<< orphan*/ *,struct config_registers const*) ; 
 struct of_device_id* of_match_device (int /*<<< orphan*/ ,TYPE_1__*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 struct config_registers v2_config_registers ; 
 struct config_registers v4_config_registers ; 
 struct config_registers v5_config_registers ; 
 struct config_registers v6_config_registers ; 

__attribute__((used)) static int hwicap_drv_probe(struct platform_device *pdev)
{
	const struct of_device_id *match;
	struct resource *res;
	const struct config_registers *regs;
	const char *family;

	match = of_match_device(hwicap_of_match, &pdev->dev);
	if (match)
		return hwicap_of_probe(pdev, match->data);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res)
		return -ENODEV;

	/* It's most likely that we're using V4, if the family is not
	 * specified
	 */
	regs = &v4_config_registers;
	family = pdev->dev.platform_data;

	if (family) {
		if (!strcmp(family, "virtex2p"))
			regs = &v2_config_registers;
		else if (!strcmp(family, "virtex4"))
			regs = &v4_config_registers;
		else if (!strcmp(family, "virtex5"))
			regs = &v5_config_registers;
		else if (!strcmp(family, "virtex6"))
			regs = &v6_config_registers;
	}

	return hwicap_setup(&pdev->dev, pdev->id, res,
			&buffer_icap_config, regs);
}