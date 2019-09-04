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
struct pci_dev {int /*<<< orphan*/  msi_cap; } ;
struct intel_gvt_device_info {int max_support_vgpus; int mmio_size; int gtt_start_offset; int gtt_entry_size; int gtt_entry_size_shift; int gmadr_bytes_in_cmd; int max_surface_size; int /*<<< orphan*/  msi_cap_offset; scalar_t__ mmio_bar; int /*<<< orphan*/  cfg_space_size; } ;
struct intel_gvt {TYPE_2__* dev_priv; struct intel_gvt_device_info device_info; } ;
struct TYPE_3__ {struct pci_dev* pdev; } ;
struct TYPE_4__ {TYPE_1__ drm; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCI_CFG_SPACE_EXP_SIZE ; 

__attribute__((used)) static void init_device_info(struct intel_gvt *gvt)
{
	struct intel_gvt_device_info *info = &gvt->device_info;
	struct pci_dev *pdev = gvt->dev_priv->drm.pdev;

	info->max_support_vgpus = 8;
	info->cfg_space_size = PCI_CFG_SPACE_EXP_SIZE;
	info->mmio_size = 2 * 1024 * 1024;
	info->mmio_bar = 0;
	info->gtt_start_offset = 8 * 1024 * 1024;
	info->gtt_entry_size = 8;
	info->gtt_entry_size_shift = 3;
	info->gmadr_bytes_in_cmd = 8;
	info->max_surface_size = 36 * 1024 * 1024;
	info->msi_cap_offset = pdev->msi_cap;
}