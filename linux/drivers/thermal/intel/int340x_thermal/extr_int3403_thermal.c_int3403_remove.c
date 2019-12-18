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
struct int3403_priv {int type; } ;

/* Variables and functions */
#define  INT3403_TYPE_BATTERY 130 
#define  INT3403_TYPE_CHARGER 129 
#define  INT3403_TYPE_SENSOR 128 
 int /*<<< orphan*/  int3403_cdev_remove (struct int3403_priv*) ; 
 int /*<<< orphan*/  int3403_sensor_remove (struct int3403_priv*) ; 
 struct int3403_priv* platform_get_drvdata (struct platform_device*) ; 

__attribute__((used)) static int int3403_remove(struct platform_device *pdev)
{
	struct int3403_priv *priv = platform_get_drvdata(pdev);

	switch (priv->type) {
	case INT3403_TYPE_SENSOR:
		int3403_sensor_remove(priv);
		break;
	case INT3403_TYPE_CHARGER:
	case INT3403_TYPE_BATTERY:
		int3403_cdev_remove(priv);
		break;
	default:
		break;
	}

	return 0;
}