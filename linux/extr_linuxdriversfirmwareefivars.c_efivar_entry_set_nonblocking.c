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
typedef  int /*<<< orphan*/  u32 ;
struct efivar_operations {scalar_t__ (* set_variable_nonblocking ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,void*) ;} ;
typedef  scalar_t__ efi_status_t ;
typedef  int /*<<< orphan*/  efi_guid_t ;
typedef  int /*<<< orphan*/  efi_char16_t ;
struct TYPE_2__ {struct efivar_operations* ops; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ EFI_SUCCESS ; 
 int EINVAL ; 
 int ENOSPC ; 
 TYPE_1__* __efivars ; 
 scalar_t__ check_var_size_nonblocking (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ down_trylock (int /*<<< orphan*/ *) ; 
 int efi_status_to_err (scalar_t__) ; 
 int /*<<< orphan*/  efivars_lock ; 
 scalar_t__ stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long,void*) ; 
 scalar_t__ ucs2_strsize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
efivar_entry_set_nonblocking(efi_char16_t *name, efi_guid_t vendor,
			     u32 attributes, unsigned long size, void *data)
{
	const struct efivar_operations *ops;
	efi_status_t status;

	if (down_trylock(&efivars_lock))
		return -EBUSY;

	if (!__efivars) {
		up(&efivars_lock);
		return -EINVAL;
	}

	status = check_var_size_nonblocking(attributes,
					    size + ucs2_strsize(name, 1024));
	if (status != EFI_SUCCESS) {
		up(&efivars_lock);
		return -ENOSPC;
	}

	ops = __efivars->ops;
	status = ops->set_variable_nonblocking(name, &vendor, attributes,
					       size, data);

	up(&efivars_lock);
	return efi_status_to_err(status);
}