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
typedef  int /*<<< orphan*/  u32 ;
struct list_head {int dummy; } ;
struct efivar_operations {scalar_t__ (* set_variable ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,void*) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  VendorGuid; int /*<<< orphan*/ * VariableName; } ;
struct efivar_entry {TYPE_1__ var; } ;
typedef  scalar_t__ efi_status_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;
typedef  int /*<<< orphan*/  efi_char16_t ;
struct TYPE_4__ {struct efivar_operations* ops; } ;

/* Variables and functions */
 int EEXIST ; 
 scalar_t__ EFI_SUCCESS ; 
 scalar_t__ EFI_UNSUPPORTED ; 
 int EINTR ; 
 int EINVAL ; 
 TYPE_2__* __efivars ; 
 scalar_t__ check_var_size (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ down_interruptible (int /*<<< orphan*/ *) ; 
 int efi_status_to_err (scalar_t__) ; 
 scalar_t__ efivar_entry_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct list_head*,int) ; 
 int /*<<< orphan*/  efivars_lock ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,void*) ; 
 scalar_t__ ucs2_strsize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int efivar_entry_set(struct efivar_entry *entry, u32 attributes,
		     unsigned long size, void *data, struct list_head *head)
{
	const struct efivar_operations *ops;
	efi_status_t status;
	efi_char16_t *name = entry->var.VariableName;
	efi_guid_t vendor = entry->var.VendorGuid;

	if (down_interruptible(&efivars_lock))
		return -EINTR;

	if (!__efivars) {
		up(&efivars_lock);
		return -EINVAL;
	}
	ops = __efivars->ops;
	if (head && efivar_entry_find(name, vendor, head, false)) {
		up(&efivars_lock);
		return -EEXIST;
	}

	status = check_var_size(attributes, size + ucs2_strsize(name, 1024));
	if (status == EFI_SUCCESS || status == EFI_UNSUPPORTED)
		status = ops->set_variable(name, &vendor,
					   attributes, size, data);

	up(&efivars_lock);

	return efi_status_to_err(status);

}