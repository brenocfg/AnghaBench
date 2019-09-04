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
struct ioc {int /*<<< orphan*/  handle; struct ioc* next; } ;
struct acpi_device_id {int dummy; } ;
struct acpi_device {int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct ioc* ioc_found ; 
 struct ioc* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int acpi_sba_ioc_attach(struct acpi_device *device,
			       const struct acpi_device_id *not_used)
{
	struct ioc *ioc;

	ioc = kzalloc(sizeof(*ioc), GFP_KERNEL);
	if (!ioc)
		return -ENOMEM;

	ioc->next = ioc_found;
	ioc_found = ioc;
	ioc->handle = device->handle;
	return 1;
}