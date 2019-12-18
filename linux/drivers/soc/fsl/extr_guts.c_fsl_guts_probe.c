#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct resource {int dummy; } ;
struct device {struct device_node* of_node; } ;
struct platform_device {struct device dev; } ;
struct fsl_soc_die_attr {int /*<<< orphan*/  die; } ;
struct device_node {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  regs; int /*<<< orphan*/  little_endian; } ;
struct TYPE_5__ {char const* machine; void* revision; void* soc_id; void* family; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  devm_ioremap_resource (struct device*,struct resource*) ; 
 void* devm_kasprintf (struct device*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_3__* devm_kzalloc (struct device*,int,int /*<<< orphan*/ ) ; 
 int fsl_guts_get_svr () ; 
 int /*<<< orphan*/  fsl_soc_die ; 
 struct fsl_soc_die_attr* fsl_soc_die_match (int,int /*<<< orphan*/ ) ; 
 TYPE_3__* guts ; 
 int /*<<< orphan*/  of_find_node_by_path (char*) ; 
 int /*<<< orphan*/  of_property_read_bool (struct device_node*,char*) ; 
 scalar_t__ of_property_read_string (int /*<<< orphan*/ ,char*,char const**) ; 
 int /*<<< orphan*/  of_property_read_string_index (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char const**) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,char const*,...) ; 
 int /*<<< orphan*/  root ; 
 int /*<<< orphan*/  soc_dev ; 
 TYPE_1__ soc_dev_attr ; 
 int /*<<< orphan*/  soc_device_register (TYPE_1__*) ; 

__attribute__((used)) static int fsl_guts_probe(struct platform_device *pdev)
{
	struct device_node *np = pdev->dev.of_node;
	struct device *dev = &pdev->dev;
	struct resource *res;
	const struct fsl_soc_die_attr *soc_die;
	const char *machine;
	u32 svr;

	/* Initialize guts */
	guts = devm_kzalloc(dev, sizeof(*guts), GFP_KERNEL);
	if (!guts)
		return -ENOMEM;

	guts->little_endian = of_property_read_bool(np, "little-endian");

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	guts->regs = devm_ioremap_resource(dev, res);
	if (IS_ERR(guts->regs))
		return PTR_ERR(guts->regs);

	/* Register soc device */
	root = of_find_node_by_path("/");
	if (of_property_read_string(root, "model", &machine))
		of_property_read_string_index(root, "compatible", 0, &machine);
	if (machine)
		soc_dev_attr.machine = machine;

	svr = fsl_guts_get_svr();
	soc_die = fsl_soc_die_match(svr, fsl_soc_die);
	if (soc_die) {
		soc_dev_attr.family = devm_kasprintf(dev, GFP_KERNEL,
						     "QorIQ %s", soc_die->die);
	} else {
		soc_dev_attr.family = devm_kasprintf(dev, GFP_KERNEL, "QorIQ");
	}
	if (!soc_dev_attr.family)
		return -ENOMEM;
	soc_dev_attr.soc_id = devm_kasprintf(dev, GFP_KERNEL,
					     "svr:0x%08x", svr);
	if (!soc_dev_attr.soc_id)
		return -ENOMEM;
	soc_dev_attr.revision = devm_kasprintf(dev, GFP_KERNEL, "%d.%d",
					       (svr >>  4) & 0xf, svr & 0xf);
	if (!soc_dev_attr.revision)
		return -ENOMEM;

	soc_dev = soc_device_register(&soc_dev_attr);
	if (IS_ERR(soc_dev))
		return PTR_ERR(soc_dev);

	pr_info("Machine: %s\n", soc_dev_attr.machine);
	pr_info("SoC family: %s\n", soc_dev_attr.family);
	pr_info("SoC ID: %s, Revision: %s\n",
		soc_dev_attr.soc_id, soc_dev_attr.revision);
	return 0;
}