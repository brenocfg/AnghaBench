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
typedef  int /*<<< orphan*/  u16 ;
struct kvmgt_guest_info {struct intel_vgpu* vgpu; } ;
struct TYPE_2__ {int /*<<< orphan*/ * msi_trigger; } ;
struct intel_vgpu {TYPE_1__ vdev; } ;

/* Variables and functions */
 int EFAULT ; 
 int ESRCH ; 
 int eventfd_signal (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  handle_valid (unsigned long) ; 

__attribute__((used)) static int kvmgt_inject_msi(unsigned long handle, u32 addr, u16 data)
{
	struct kvmgt_guest_info *info;
	struct intel_vgpu *vgpu;

	if (!handle_valid(handle))
		return -ESRCH;

	info = (struct kvmgt_guest_info *)handle;
	vgpu = info->vgpu;

	/*
	 * When guest is poweroff, msi_trigger is set to NULL, but vgpu's
	 * config and mmio register isn't restored to default during guest
	 * poweroff. If this vgpu is still used in next vm, this vgpu's pipe
	 * may be enabled, then once this vgpu is active, it will get inject
	 * vblank interrupt request. But msi_trigger is null until msi is
	 * enabled by guest. so if msi_trigger is null, success is still
	 * returned and don't inject interrupt into guest.
	 */
	if (vgpu->vdev.msi_trigger == NULL)
		return 0;

	if (eventfd_signal(vgpu->vdev.msi_trigger, 1) == 1)
		return 0;

	return -EFAULT;
}