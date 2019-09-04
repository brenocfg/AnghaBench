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
struct soc_camera_platform_priv {int /*<<< orphan*/  subdev; } ;
struct soc_camera_platform_info {TYPE_1__* icd; } ;
struct platform_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * control; } ;

/* Variables and functions */
 struct soc_camera_platform_priv* get_priv (struct platform_device*) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (int /*<<< orphan*/ *) ; 
 struct soc_camera_platform_info* v4l2_get_subdevdata (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int soc_camera_platform_remove(struct platform_device *pdev)
{
	struct soc_camera_platform_priv *priv = get_priv(pdev);
	struct soc_camera_platform_info *p = v4l2_get_subdevdata(&priv->subdev);

	p->icd->control = NULL;
	v4l2_device_unregister_subdev(&priv->subdev);
	return 0;
}