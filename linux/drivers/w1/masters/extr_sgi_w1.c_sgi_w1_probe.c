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
struct sgi_w1_platform_data {int /*<<< orphan*/  dev_id; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_id; int /*<<< orphan*/  touch_bit; int /*<<< orphan*/  reset_bus; struct sgi_w1_device* data; } ;
struct sgi_w1_device {TYPE_1__ bus_master; int /*<<< orphan*/  dev_id; int /*<<< orphan*/  mcr; } ;
struct resource {int dummy; } ;
struct platform_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 struct sgi_w1_platform_data* dev_get_platdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  devm_ioremap_resource (int /*<<< orphan*/ *,struct resource*) ; 
 struct sgi_w1_device* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct sgi_w1_device*) ; 
 int /*<<< orphan*/  sgi_w1_reset_bus ; 
 int /*<<< orphan*/  sgi_w1_touch_bit ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int w1_add_master_device (TYPE_1__*) ; 

__attribute__((used)) static int sgi_w1_probe(struct platform_device *pdev)
{
	struct sgi_w1_device *sdev;
	struct sgi_w1_platform_data *pdata;
	struct resource *res;

	sdev = devm_kzalloc(&pdev->dev, sizeof(struct sgi_w1_device),
			    GFP_KERNEL);
	if (!sdev)
		return -ENOMEM;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
	sdev->mcr = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(sdev->mcr))
		return PTR_ERR(sdev->mcr);

	sdev->bus_master.data = sdev;
	sdev->bus_master.reset_bus = sgi_w1_reset_bus;
	sdev->bus_master.touch_bit = sgi_w1_touch_bit;

	pdata = dev_get_platdata(&pdev->dev);
	if (pdata) {
		strlcpy(sdev->dev_id, pdata->dev_id, sizeof(sdev->dev_id));
		sdev->bus_master.dev_id = sdev->dev_id;
	}

	platform_set_drvdata(pdev, sdev);

	return w1_add_master_device(&sdev->bus_master);
}