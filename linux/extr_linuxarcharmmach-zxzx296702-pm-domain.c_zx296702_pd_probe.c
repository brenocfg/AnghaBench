#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct resource {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct genpd_onecell_data {int num_domains; int /*<<< orphan*/ * domains; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int EIO ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct genpd_onecell_data* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_genpd_add_provider_onecell (int /*<<< orphan*/ ,struct genpd_onecell_data*) ; 
 int /*<<< orphan*/  pcubase ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_genpd_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * zx296702_pm_domains ; 

__attribute__((used)) static int zx296702_pd_probe(struct platform_device *pdev)
{
	struct genpd_onecell_data *genpd_data;
	struct resource *res;
	int i;

	genpd_data = devm_kzalloc(&pdev->dev, sizeof(*genpd_data), GFP_KERNEL);
	if (!genpd_data)
		return -ENOMEM;

	genpd_data->domains = zx296702_pm_domains;
	genpd_data->num_domains = ARRAY_SIZE(zx296702_pm_domains);

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	if (!res) {
		dev_err(&pdev->dev, "no memory resource defined\n");
		return -ENODEV;
	}

	pcubase = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(pcubase)) {
		dev_err(&pdev->dev, "ioremap fail.\n");
		return -EIO;
	}

	for (i = 0; i < ARRAY_SIZE(zx296702_pm_domains); ++i)
		pm_genpd_init(zx296702_pm_domains[i], NULL, false);

	of_genpd_add_provider_onecell(pdev->dev.of_node, genpd_data);
	return 0;
}