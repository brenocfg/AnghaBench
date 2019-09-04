#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  VendorGuid; int /*<<< orphan*/  VariableName; } ;
struct efivar_entry {TYPE_2__ var; } ;
typedef  int /*<<< orphan*/  efi_status_t ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* set_variable ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_3__* __efivars ; 
 int efi_status_to_err (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int __efivar_entry_delete(struct efivar_entry *entry)
{
	efi_status_t status;

	if (!__efivars)
		return -EINVAL;

	status = __efivars->ops->set_variable(entry->var.VariableName,
					      &entry->var.VendorGuid,
					      0, 0, NULL);

	return efi_status_to_err(status);
}