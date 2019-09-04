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
struct acpi_hardware_id {int /*<<< orphan*/  list; int /*<<< orphan*/  id; } ;
struct TYPE_2__ {int hardware_id; } ;
struct acpi_device_pnp {TYPE_1__ type; int /*<<< orphan*/  ids; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  kfree (struct acpi_hardware_id*) ; 
 struct acpi_hardware_id* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kstrdup_const (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acpi_add_id(struct acpi_device_pnp *pnp, const char *dev_id)
{
	struct acpi_hardware_id *id;

	id = kmalloc(sizeof(*id), GFP_KERNEL);
	if (!id)
		return;

	id->id = kstrdup_const(dev_id, GFP_KERNEL);
	if (!id->id) {
		kfree(id);
		return;
	}

	list_add_tail(&id->list, &pnp->ids);
	pnp->type.hardware_id = 1;
}