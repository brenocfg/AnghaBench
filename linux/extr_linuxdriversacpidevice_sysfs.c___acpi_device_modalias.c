#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  of_compatible; } ;
struct TYPE_4__ {int /*<<< orphan*/  ids; } ;
struct acpi_device {TYPE_1__ data; TYPE_2__ pnp; } ;

/* Variables and functions */
 int ENODEV ; 
 int create_of_modalias (struct acpi_device*,char*,int) ; 
 int create_pnp_modalias (struct acpi_device*,char*,int) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __acpi_device_modalias(struct acpi_device *adev, char *buf, int size)
{
	int len, count;

	if (!adev)
		return -ENODEV;

	if (list_empty(&adev->pnp.ids))
		return 0;

	len = create_pnp_modalias(adev, buf, size - 1);
	if (len < 0) {
		return len;
	} else if (len > 0) {
		buf[len++] = '\n';
		size -= len;
	}
	if (!adev->data.of_compatible)
		return len;

	count = create_of_modalias(adev, buf + len, size - 1);
	if (count < 0) {
		return count;
	} else if (count > 0) {
		len += count;
		buf[len++] = '\n';
	}

	return len;
}