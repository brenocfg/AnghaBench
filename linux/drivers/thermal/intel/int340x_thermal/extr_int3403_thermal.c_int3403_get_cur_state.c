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
struct thermal_cooling_device {struct int3403_priv* devdata; } ;
struct int3403_priv {TYPE_1__* adev; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 

__attribute__((used)) static int int3403_get_cur_state(struct thermal_cooling_device *cdev,
				 unsigned long *state)
{
	struct int3403_priv *priv = cdev->devdata;
	unsigned long long level;
	acpi_status status;

	status = acpi_evaluate_integer(priv->adev->handle, "PPPC", NULL, &level);
	if (ACPI_SUCCESS(status)) {
		*state = level;
		return 0;
	} else
		return -EINVAL;
}