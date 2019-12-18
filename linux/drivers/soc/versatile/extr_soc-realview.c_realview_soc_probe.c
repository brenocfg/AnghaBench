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
struct soc_device_attribute {char* machine; char* family; int /*<<< orphan*/  soc_id; } ;
struct soc_device {int dummy; } ;
typedef  struct soc_device regmap ;
struct TYPE_2__ {struct device_node* of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct soc_device*) ; 
 int PTR_ERR (struct soc_device*) ; 
 int /*<<< orphan*/  REALVIEW_SYS_ID_OFFSET ; 
 int /*<<< orphan*/  dev_info (TYPE_1__*,char*,int,int) ; 
 int /*<<< orphan*/  device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct soc_device_attribute*) ; 
 struct soc_device_attribute* kzalloc (int,int /*<<< orphan*/ ) ; 
 int of_property_read_string (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  realview_arch_attr ; 
 int /*<<< orphan*/  realview_board_attr ; 
 int /*<<< orphan*/  realview_build_attr ; 
 int realview_coreid ; 
 int /*<<< orphan*/  realview_manf_attr ; 
 int regmap_read (struct soc_device*,int /*<<< orphan*/ ,int*) ; 
 struct soc_device* soc_device_register (struct soc_device_attribute*) ; 
 int /*<<< orphan*/  soc_device_to_device (struct soc_device*) ; 
 struct soc_device* syscon_regmap_lookup_by_phandle (struct device_node*,char*) ; 

__attribute__((used)) static int realview_soc_probe(struct platform_device *pdev)
{
	struct regmap *syscon_regmap;
	struct soc_device *soc_dev;
	struct soc_device_attribute *soc_dev_attr;
	struct device_node *np = pdev->dev.of_node;
	int ret;

	syscon_regmap = syscon_regmap_lookup_by_phandle(np, "regmap");
	if (IS_ERR(syscon_regmap))
		return PTR_ERR(syscon_regmap);

	soc_dev_attr = kzalloc(sizeof(*soc_dev_attr), GFP_KERNEL);
	if (!soc_dev_attr)
		return -ENOMEM;

	ret = of_property_read_string(np, "compatible",
				      &soc_dev_attr->soc_id);
	if (ret)
		return -EINVAL;

	soc_dev_attr->machine = "RealView";
	soc_dev_attr->family = "Versatile";
	soc_dev = soc_device_register(soc_dev_attr);
	if (IS_ERR(soc_dev)) {
		kfree(soc_dev_attr);
		return -ENODEV;
	}
	ret = regmap_read(syscon_regmap, REALVIEW_SYS_ID_OFFSET,
			  &realview_coreid);
	if (ret)
		return -ENODEV;

	device_create_file(soc_device_to_device(soc_dev), &realview_manf_attr);
	device_create_file(soc_device_to_device(soc_dev), &realview_board_attr);
	device_create_file(soc_device_to_device(soc_dev), &realview_arch_attr);
	device_create_file(soc_device_to_device(soc_dev), &realview_build_attr);

	dev_info(&pdev->dev, "RealView Syscon Core ID: 0x%08x, HBI-%03x\n",
		 realview_coreid,
		 ((realview_coreid >> 16) & 0xfff));
	/* FIXME: add attributes for SoC to sysfs */
	return 0;
}