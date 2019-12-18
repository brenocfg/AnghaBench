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
struct resource {int /*<<< orphan*/  start; } ;
struct platform_device_id {int /*<<< orphan*/  driver_data; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;
struct osd_state {int /*<<< orphan*/ * dev; int /*<<< orphan*/  ops; int /*<<< orphan*/  lock; int /*<<< orphan*/  osd_size; int /*<<< orphan*/  osd_base_phys; int /*<<< orphan*/  osd_base; int /*<<< orphan*/  vpbe_type; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_notice (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct osd_state* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  osd_ops ; 
 struct platform_device_id* platform_get_device_id (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct osd_state*) ; 
 int /*<<< orphan*/  resource_size (struct resource*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int osd_probe(struct platform_device *pdev)
{
	const struct platform_device_id *pdev_id;
	struct osd_state *osd;
	struct resource *res;

	pdev_id = platform_get_device_id(pdev);
	if (!pdev_id)
		return -EINVAL;

	osd = devm_kzalloc(&pdev->dev, sizeof(struct osd_state), GFP_KERNEL);
	if (osd == NULL)
		return -ENOMEM;


	osd->dev = &pdev->dev;
	osd->vpbe_type = pdev_id->driver_data;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	osd->osd_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(osd->osd_base))
		return PTR_ERR(osd->osd_base);

	osd->osd_base_phys = res->start;
	osd->osd_size = resource_size(res);
	spin_lock_init(&osd->lock);
	osd->ops = osd_ops;
	platform_set_drvdata(pdev, osd);
	dev_notice(osd->dev, "OSD sub device probe success\n");

	return 0;
}