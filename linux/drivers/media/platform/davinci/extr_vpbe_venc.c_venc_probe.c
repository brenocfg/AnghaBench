#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct venc_state {scalar_t__ venc_type; TYPE_1__* pdev; int /*<<< orphan*/  lock; void* vdaccfg_reg; void* venc_base; scalar_t__ pdata; } ;
struct resource {int dummy; } ;
struct platform_device_id {scalar_t__ driver_data; } ;
struct TYPE_5__ {scalar_t__ platform_data; } ;
struct platform_device {TYPE_1__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IORESOURCE_MEM ; 
 scalar_t__ IS_ERR (void*) ; 
 int PTR_ERR (void*) ; 
 scalar_t__ VPBE_VERSION_1 ; 
 int /*<<< orphan*/  dev_err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  dev_notice (TYPE_1__*,char*) ; 
 void* devm_ioremap_resource (TYPE_1__*,struct resource*) ; 
 struct venc_state* devm_kzalloc (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 struct platform_device_id* platform_get_device_id (struct platform_device*) ; 
 struct resource* platform_get_resource (struct platform_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct venc_state*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int venc_probe(struct platform_device *pdev)
{
	const struct platform_device_id *pdev_id;
	struct venc_state *venc;
	struct resource *res;

	if (!pdev->dev.platform_data) {
		dev_err(&pdev->dev, "No platform data for VENC sub device");
		return -EINVAL;
	}

	pdev_id = platform_get_device_id(pdev);
	if (!pdev_id)
		return -EINVAL;

	venc = devm_kzalloc(&pdev->dev, sizeof(struct venc_state), GFP_KERNEL);
	if (venc == NULL)
		return -ENOMEM;

	venc->venc_type = pdev_id->driver_data;
	venc->pdev = &pdev->dev;
	venc->pdata = pdev->dev.platform_data;

	res = platform_get_resource(pdev, IORESOURCE_MEM, 0);

	venc->venc_base = devm_ioremap_resource(&pdev->dev, res);
	if (IS_ERR(venc->venc_base))
		return PTR_ERR(venc->venc_base);

	if (venc->venc_type != VPBE_VERSION_1) {
		res = platform_get_resource(pdev, IORESOURCE_MEM, 1);

		venc->vdaccfg_reg = devm_ioremap_resource(&pdev->dev, res);
		if (IS_ERR(venc->vdaccfg_reg))
			return PTR_ERR(venc->vdaccfg_reg);
	}
	spin_lock_init(&venc->lock);
	platform_set_drvdata(pdev, venc);
	dev_notice(venc->pdev, "VENC sub device probe success\n");

	return 0;
}