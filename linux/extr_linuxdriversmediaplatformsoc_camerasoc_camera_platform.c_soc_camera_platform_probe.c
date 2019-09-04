#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct soc_camera_platform_priv {TYPE_1__ subdev; } ;
struct soc_camera_platform_info {struct soc_camera_device* icd; } ;
struct soc_camera_host {int /*<<< orphan*/  v4l2_dev; } ;
struct soc_camera_device {int /*<<< orphan*/  parent; TYPE_5__* control; } ;
struct TYPE_9__ {struct soc_camera_platform_info* platform_data; } ;
struct platform_device {TYPE_5__ dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  dev_name (TYPE_5__*) ; 
 struct soc_camera_platform_priv* devm_kzalloc (TYPE_5__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,TYPE_1__*) ; 
 int /*<<< orphan*/  platform_subdev_ops ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct soc_camera_host* to_soc_camera_host (int /*<<< orphan*/ ) ; 
 int v4l2_device_register_subdev (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  v4l2_set_subdevdata (TYPE_1__*,struct soc_camera_platform_info*) ; 
 int /*<<< orphan*/  v4l2_subdev_init (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int soc_camera_platform_probe(struct platform_device *pdev)
{
	struct soc_camera_host *ici;
	struct soc_camera_platform_priv *priv;
	struct soc_camera_platform_info *p = pdev->dev.platform_data;
	struct soc_camera_device *icd;

	if (!p)
		return -EINVAL;

	if (!p->icd) {
		dev_err(&pdev->dev,
			"Platform has not set soc_camera_device pointer!\n");
		return -EINVAL;
	}

	priv = devm_kzalloc(&pdev->dev, sizeof(*priv), GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	icd = p->icd;

	/* soc-camera convention: control's drvdata points to the subdev */
	platform_set_drvdata(pdev, &priv->subdev);
	/* Set the control device reference */
	icd->control = &pdev->dev;

	ici = to_soc_camera_host(icd->parent);

	v4l2_subdev_init(&priv->subdev, &platform_subdev_ops);
	v4l2_set_subdevdata(&priv->subdev, p);
	strlcpy(priv->subdev.name, dev_name(&pdev->dev),
		sizeof(priv->subdev.name));

	return v4l2_device_register_subdev(&ici->v4l2_dev, &priv->subdev);
}