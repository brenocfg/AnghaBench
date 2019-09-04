#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_8__ {TYPE_2__* bar; } ;
struct intel_vgpu {TYPE_3__ cfg_space; struct intel_gvt* gvt; } ;
struct intel_gvt_device_info {int /*<<< orphan*/  cfg_space_size; } ;
struct TYPE_6__ {int /*<<< orphan*/  cfg_space; } ;
struct intel_gvt {TYPE_5__* dev_priv; TYPE_1__ firmware; struct intel_gvt_device_info device_info; } ;
struct TYPE_9__ {int /*<<< orphan*/  pdev; } ;
struct TYPE_10__ {TYPE_4__ drm; } ;
struct TYPE_7__ {void* size; } ;

/* Variables and functions */
 int BDW_GMCH_GMS_MASK ; 
 int BDW_GMCH_GMS_SHIFT ; 
 size_t INTEL_GVT_PCI_BAR_APERTURE ; 
 size_t INTEL_GVT_PCI_BAR_GTTMMIO ; 
 int INTEL_GVT_PCI_CLASS_VGA_OTHER ; 
 int INTEL_GVT_PCI_GMCH_CONTROL ; 
 int INTEL_GVT_PCI_OPREGION ; 
 int PCI_BASE_ADDRESS_1 ; 
 int /*<<< orphan*/  PCI_BASE_ADDRESS_2 ; 
 int PCI_BASE_ADDRESS_3 ; 
 int PCI_BASE_ADDRESS_4 ; 
 size_t PCI_CLASS_DEVICE ; 
 size_t PCI_CLASS_PROG ; 
 size_t PCI_COMMAND ; 
 int PCI_COMMAND_IO ; 
 int PCI_COMMAND_MASTER ; 
 int PCI_COMMAND_MEMORY ; 
 int PCI_ROM_ADDRESS ; 
 int /*<<< orphan*/  gvt_aperture_pa_base (struct intel_gvt*) ; 
 int /*<<< orphan*/  intel_vgpu_write_pci_bar (struct intel_vgpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 void* pci_resource_len (int /*<<< orphan*/ ,int) ; 
 int* vgpu_cfg_space (struct intel_vgpu*) ; 

void intel_vgpu_init_cfg_space(struct intel_vgpu *vgpu,
			       bool primary)
{
	struct intel_gvt *gvt = vgpu->gvt;
	const struct intel_gvt_device_info *info = &gvt->device_info;
	u16 *gmch_ctl;

	memcpy(vgpu_cfg_space(vgpu), gvt->firmware.cfg_space,
	       info->cfg_space_size);

	if (!primary) {
		vgpu_cfg_space(vgpu)[PCI_CLASS_DEVICE] =
			INTEL_GVT_PCI_CLASS_VGA_OTHER;
		vgpu_cfg_space(vgpu)[PCI_CLASS_PROG] =
			INTEL_GVT_PCI_CLASS_VGA_OTHER;
	}

	/* Show guest that there isn't any stolen memory.*/
	gmch_ctl = (u16 *)(vgpu_cfg_space(vgpu) + INTEL_GVT_PCI_GMCH_CONTROL);
	*gmch_ctl &= ~(BDW_GMCH_GMS_MASK << BDW_GMCH_GMS_SHIFT);

	intel_vgpu_write_pci_bar(vgpu, PCI_BASE_ADDRESS_2,
				 gvt_aperture_pa_base(gvt), true);

	vgpu_cfg_space(vgpu)[PCI_COMMAND] &= ~(PCI_COMMAND_IO
					     | PCI_COMMAND_MEMORY
					     | PCI_COMMAND_MASTER);
	/*
	 * Clear the bar upper 32bit and let guest to assign the new value
	 */
	memset(vgpu_cfg_space(vgpu) + PCI_BASE_ADDRESS_1, 0, 4);
	memset(vgpu_cfg_space(vgpu) + PCI_BASE_ADDRESS_3, 0, 4);
	memset(vgpu_cfg_space(vgpu) + PCI_BASE_ADDRESS_4, 0, 8);
	memset(vgpu_cfg_space(vgpu) + INTEL_GVT_PCI_OPREGION, 0, 4);

	vgpu->cfg_space.bar[INTEL_GVT_PCI_BAR_GTTMMIO].size =
				pci_resource_len(gvt->dev_priv->drm.pdev, 0);
	vgpu->cfg_space.bar[INTEL_GVT_PCI_BAR_APERTURE].size =
				pci_resource_len(gvt->dev_priv->drm.pdev, 2);

	memset(vgpu_cfg_space(vgpu) + PCI_ROM_ADDRESS, 0, 4);
}