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
struct regmap {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct of_device_id {scalar_t__ data; } ;
struct map_info {int /*<<< orphan*/  set_vpp; } ;
struct device_node {int dummy; } ;
typedef  enum versatile_flashprot { ____Placeholder_versatile_flashprot } versatile_flashprot ;

/* Variables and functions */
 int ENODEV ; 
#define  INTEGRATOR_AP_FLASHPROT 131 
#define  INTEGRATOR_CP_FLASHPROT 130 
 scalar_t__ IS_ERR (struct regmap*) ; 
 int PTR_ERR (struct regmap*) ; 
#define  REALVIEW_FLASHPROT 129 
#define  VERSATILE_FLASHPROT 128 
 int ap_flash_init (struct platform_device*) ; 
 int /*<<< orphan*/  ap_flash_set_vpp ; 
 int /*<<< orphan*/  cp_flash_set_vpp ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  of_device_is_compatible (struct device_node*,char*) ; 
 struct device_node* of_find_matching_node_and_match (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct of_device_id const**) ; 
 int /*<<< orphan*/  syscon_match ; 
 struct regmap* syscon_node_to_regmap (struct device_node*) ; 
 struct regmap* syscon_regmap ; 
 int /*<<< orphan*/  versatile_flash_set_vpp ; 

int of_flash_probe_versatile(struct platform_device *pdev,
			     struct device_node *np,
			     struct map_info *map)
{
	struct device_node *sysnp;
	const struct of_device_id *devid;
	struct regmap *rmap;
	static enum versatile_flashprot versatile_flashprot;
	int ret;

	/* Not all flash chips use this protection line */
	if (!of_device_is_compatible(np, "arm,versatile-flash"))
		return 0;

	/* For first chip probed, look up the syscon regmap */
	if (!syscon_regmap) {
		sysnp = of_find_matching_node_and_match(NULL,
							syscon_match,
							&devid);
		if (!sysnp)
			return -ENODEV;

		versatile_flashprot = (enum versatile_flashprot)devid->data;
		rmap = syscon_node_to_regmap(sysnp);
		if (IS_ERR(rmap))
			return PTR_ERR(rmap);

		syscon_regmap = rmap;
	}

	switch (versatile_flashprot) {
	case INTEGRATOR_AP_FLASHPROT:
		ret = ap_flash_init(pdev);
		if (ret)
			return ret;
		map->set_vpp = ap_flash_set_vpp;
		dev_info(&pdev->dev, "Integrator/AP flash protection\n");
		break;
	case INTEGRATOR_CP_FLASHPROT:
		map->set_vpp = cp_flash_set_vpp;
		dev_info(&pdev->dev, "Integrator/CP flash protection\n");
		break;
	case VERSATILE_FLASHPROT:
	case REALVIEW_FLASHPROT:
		map->set_vpp = versatile_flash_set_vpp;
		dev_info(&pdev->dev, "versatile/realview flash protection\n");
		break;
	default:
		dev_info(&pdev->dev, "device marked as Versatile flash "
			 "but no system controller was found\n");
		break;
	}

	return 0;
}