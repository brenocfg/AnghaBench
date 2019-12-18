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
struct vm_area_struct {int vm_flags; } ;
struct gasket_dev {scalar_t__ status; int /*<<< orphan*/  dev; int /*<<< orphan*/  dev_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 scalar_t__ GASKET_STATUS_ALIVE ; 
 int VM_EXEC ; 
 int VM_READ ; 
 int VM_WRITE ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  gasket_owned_by_current_tgid (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool gasket_mmap_has_permissions(struct gasket_dev *gasket_dev,
					struct vm_area_struct *vma,
					int bar_permissions)
{
	int requested_permissions;
	/* Always allow sysadmin to access. */
	if (capable(CAP_SYS_ADMIN))
		return true;

	/* Never allow non-sysadmins to access to a dead device. */
	if (gasket_dev->status != GASKET_STATUS_ALIVE) {
		dev_dbg(gasket_dev->dev, "Device is dead.\n");
		return false;
	}

	/* Make sure that no wrong flags are set. */
	requested_permissions =
		(vma->vm_flags & (VM_WRITE | VM_READ | VM_EXEC));
	if (requested_permissions & ~(bar_permissions)) {
		dev_dbg(gasket_dev->dev,
			"Attempting to map a region with requested permissions "
			"0x%x, but region has permissions 0x%x.\n",
			requested_permissions, bar_permissions);
		return false;
	}

	/* Do not allow a non-owner to write. */
	if ((vma->vm_flags & VM_WRITE) &&
	    !gasket_owned_by_current_tgid(&gasket_dev->dev_info)) {
		dev_dbg(gasket_dev->dev,
			"Attempting to mmap a region for write without owning device.\n");
		return false;
	}

	return true;
}