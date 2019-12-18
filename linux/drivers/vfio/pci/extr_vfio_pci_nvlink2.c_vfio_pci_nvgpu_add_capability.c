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
struct TYPE_2__ {int version; int /*<<< orphan*/  id; } ;
struct vfio_region_info_cap_nvlink2_ssatgt {TYPE_1__ header; int /*<<< orphan*/  tgt; } ;
struct vfio_pci_region {struct vfio_pci_nvgpu_data* data; } ;
struct vfio_pci_nvgpu_data {int /*<<< orphan*/  gpu_tgt; } ;
struct vfio_pci_device {int dummy; } ;
struct vfio_info_cap {int dummy; } ;
typedef  int /*<<< orphan*/  cap ;

/* Variables and functions */
 int /*<<< orphan*/  VFIO_REGION_INFO_CAP_NVLINK2_SSATGT ; 
 int vfio_info_add_capability (struct vfio_info_cap*,TYPE_1__*,int) ; 

__attribute__((used)) static int vfio_pci_nvgpu_add_capability(struct vfio_pci_device *vdev,
		struct vfio_pci_region *region, struct vfio_info_cap *caps)
{
	struct vfio_pci_nvgpu_data *data = region->data;
	struct vfio_region_info_cap_nvlink2_ssatgt cap = {
		.header.id = VFIO_REGION_INFO_CAP_NVLINK2_SSATGT,
		.header.version = 1,
		.tgt = data->gpu_tgt
	};

	return vfio_info_add_capability(caps, &cap.header, sizeof(cap));
}