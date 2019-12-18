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
struct input_dev {int dummy; } ;
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int chromeos_tbmc_query_switch (struct acpi_device*,struct input_dev*) ; 
 struct acpi_device* input_get_drvdata (struct input_dev*) ; 

__attribute__((used)) static int chromeos_tbmc_open(struct input_dev *idev)
{
	struct acpi_device *adev = input_get_drvdata(idev);

	return chromeos_tbmc_query_switch(adev, idev);
}