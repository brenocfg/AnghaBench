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
struct efivar_operations {scalar_t__ (* get_variable ) (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long*,int /*<<< orphan*/ *) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  VendorGuid; int /*<<< orphan*/  VariableName; } ;
struct efivar_entry {TYPE_1__ var; } ;
typedef  scalar_t__ efi_status_t ;
struct TYPE_4__ {struct efivar_operations* ops; } ;

/* Variables and functions */
 scalar_t__ EFI_BUFFER_TOO_SMALL ; 
 int EINTR ; 
 int EINVAL ; 
 TYPE_2__* __efivars ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 int efi_status_to_err (scalar_t__) ; 
 int /*<<< orphan*/  efivars_lock ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned long*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int efivar_entry_size(struct efivar_entry *entry, unsigned long *size)
{
	const struct efivar_operations *ops;
	efi_status_t status;

	*size = 0;

	if (down_interruptible(&efivars_lock))
		return -EINTR;
	if (!__efivars) {
		up(&efivars_lock);
		return -EINVAL;
	}
	ops = __efivars->ops;
	status = ops->get_variable(entry->var.VariableName,
				   &entry->var.VendorGuid, NULL, size, NULL);
	up(&efivars_lock);

	if (status != EFI_BUFFER_TOO_SMALL)
		return efi_status_to_err(status);

	return 0;
}