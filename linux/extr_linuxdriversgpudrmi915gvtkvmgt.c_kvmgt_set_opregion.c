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
struct intel_vgpu {int dummy; } ;
struct TYPE_2__ {void* va; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  OPREGION_SIGNATURE ; 
 int /*<<< orphan*/  OPREGION_SIZE ; 
 int PCI_VENDOR_ID_INTEL ; 
 int /*<<< orphan*/  VFIO_REGION_INFO_FLAG_READ ; 
 int /*<<< orphan*/  VFIO_REGION_SUBTYPE_INTEL_IGD_OPREGION ; 
 int VFIO_REGION_TYPE_PCI_VENDOR_TYPE ; 
 int intel_vgpu_register_reg (struct intel_vgpu*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  intel_vgpu_regops_opregion ; 
 scalar_t__ memcmp (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memunmap (void*) ; 
 TYPE_1__* vgpu_opregion (struct intel_vgpu*) ; 

__attribute__((used)) static int kvmgt_set_opregion(void *p_vgpu)
{
	struct intel_vgpu *vgpu = (struct intel_vgpu *)p_vgpu;
	void *base;
	int ret;

	/* Each vgpu has its own opregion, although VFIO would create another
	 * one later. This one is used to expose opregion to VFIO. And the
	 * other one created by VFIO later, is used by guest actually.
	 */
	base = vgpu_opregion(vgpu)->va;
	if (!base)
		return -ENOMEM;

	if (memcmp(base, OPREGION_SIGNATURE, 16)) {
		memunmap(base);
		return -EINVAL;
	}

	ret = intel_vgpu_register_reg(vgpu,
			PCI_VENDOR_ID_INTEL | VFIO_REGION_TYPE_PCI_VENDOR_TYPE,
			VFIO_REGION_SUBTYPE_INTEL_IGD_OPREGION,
			&intel_vgpu_regops_opregion, OPREGION_SIZE,
			VFIO_REGION_INFO_FLAG_READ, base);

	return ret;
}