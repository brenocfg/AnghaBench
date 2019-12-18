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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct int3403_priv {unsigned long long type; TYPE_1__* adev; struct platform_device* pdev; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 TYPE_1__* ACPI_COMPANION (int /*<<< orphan*/ *) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  INT3403_TYPE_BATTERY 130 
#define  INT3403_TYPE_CHARGER 129 
#define  INT3403_TYPE_SENSOR 128 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 struct int3403_priv* devm_kzalloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int int3403_cdev_add (struct int3403_priv*) ; 
 int int3403_sensor_add (struct int3403_priv*) ; 
 int /*<<< orphan*/  platform_set_drvdata (struct platform_device*,struct int3403_priv*) ; 

__attribute__((used)) static int int3403_add(struct platform_device *pdev)
{
	struct int3403_priv *priv;
	int result = 0;
	unsigned long long tmp;
	acpi_status status;

	priv = devm_kzalloc(&pdev->dev, sizeof(struct int3403_priv),
			    GFP_KERNEL);
	if (!priv)
		return -ENOMEM;

	priv->pdev = pdev;
	priv->adev = ACPI_COMPANION(&(pdev->dev));
	if (!priv->adev) {
		result = -EINVAL;
		goto err;
	}


	status = acpi_evaluate_integer(priv->adev->handle, "_TMP",
				       NULL, &tmp);
	if (ACPI_FAILURE(status)) {
		status = acpi_evaluate_integer(priv->adev->handle, "PTYP",
				       NULL, &priv->type);
		if (ACPI_FAILURE(status)) {
			result = -EINVAL;
			goto err;
		}
	} else {
		priv->type = INT3403_TYPE_SENSOR;
	}

	platform_set_drvdata(pdev, priv);
	switch (priv->type) {
	case INT3403_TYPE_SENSOR:
		result = int3403_sensor_add(priv);
		break;
	case INT3403_TYPE_CHARGER:
	case INT3403_TYPE_BATTERY:
		result = int3403_cdev_add(priv);
		break;
	default:
		result = -EINVAL;
	}

	if (result)
		goto err;
	return result;

err:
	return result;
}