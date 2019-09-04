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
struct platform_device {int dummy; } ;
struct of_device_id {struct atmel_pmecc_caps* data; } ;
struct device_node {int dummy; } ;
struct device {int /*<<< orphan*/  of_node; } ;
struct atmel_pmecc_caps {int dummy; } ;
struct atmel_pmecc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 struct atmel_pmecc* ERR_PTR (int /*<<< orphan*/ ) ; 
 struct atmel_pmecc_caps at91sam9g45_caps ; 
 struct atmel_pmecc* atmel_pmecc_create (struct platform_device*,struct atmel_pmecc_caps const*,int,int) ; 
 struct atmel_pmecc* atmel_pmecc_get_by_node (struct device*,struct device_node*) ; 
 int /*<<< orphan*/  atmel_pmecc_legacy_match ; 
 struct of_device_id* of_match_node (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 struct device_node* of_parse_phandle (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_property_read_bool (int /*<<< orphan*/ ,char*) ; 
 struct platform_device* to_platform_device (struct device*) ; 

struct atmel_pmecc *devm_atmel_pmecc_get(struct device *userdev)
{
	struct atmel_pmecc *pmecc;
	struct device_node *np;

	if (!userdev)
		return ERR_PTR(-EINVAL);

	if (!userdev->of_node)
		return NULL;

	np = of_parse_phandle(userdev->of_node, "ecc-engine", 0);
	if (np) {
		pmecc = atmel_pmecc_get_by_node(userdev, np);
		of_node_put(np);
	} else {
		/*
		 * Support old DT bindings: in this case the PMECC iomem
		 * resources are directly defined in the user pdev at position
		 * 1 and 2. Extract all relevant information from there.
		 */
		struct platform_device *pdev = to_platform_device(userdev);
		const struct atmel_pmecc_caps *caps;
		const struct of_device_id *match;

		/* No PMECC engine available. */
		if (!of_property_read_bool(userdev->of_node,
					   "atmel,has-pmecc"))
			return NULL;

		caps = &at91sam9g45_caps;

		/* Find the caps associated to the NAND dev node. */
		match = of_match_node(atmel_pmecc_legacy_match,
				      userdev->of_node);
		if (match && match->data)
			caps = match->data;

		pmecc = atmel_pmecc_create(pdev, caps, 1, 2);
	}

	return pmecc;
}