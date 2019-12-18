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
struct vfio_region_info_cap_nvlink2_lnkspd {TYPE_1__ header; int /*<<< orphan*/  link_speed; } ;
struct vfio_pci_region {struct vfio_pci_npu2_data* data; } ;
struct vfio_pci_npu2_data {int /*<<< orphan*/  link_speed; int /*<<< orphan*/  gpu_tgt; } ;
struct vfio_pci_device {int dummy; } ;
struct vfio_info_cap {int dummy; } ;
typedef  int /*<<< orphan*/  captgt ;
typedef  int /*<<< orphan*/  capspd ;

/* Variables and functions */
 int /*<<< orphan*/  VFIO_REGION_INFO_CAP_NVLINK2_LNKSPD ; 
 int /*<<< orphan*/  VFIO_REGION_INFO_CAP_NVLINK2_SSATGT ; 
 int vfio_info_add_capability (struct vfio_info_cap*,TYPE_1__*,int) ; 

__attribute__((used)) static int vfio_pci_npu2_add_capability(struct vfio_pci_device *vdev,
		struct vfio_pci_region *region, struct vfio_info_cap *caps)
{
	struct vfio_pci_npu2_data *data = region->data;
	struct vfio_region_info_cap_nvlink2_ssatgt captgt = {
		.header.id = VFIO_REGION_INFO_CAP_NVLINK2_SSATGT,
		.header.version = 1,
		.tgt = data->gpu_tgt
	};
	struct vfio_region_info_cap_nvlink2_lnkspd capspd = {
		.header.id = VFIO_REGION_INFO_CAP_NVLINK2_LNKSPD,
		.header.version = 1,
		.link_speed = data->link_speed
	};
	int ret;

	ret = vfio_info_add_capability(caps, &captgt.header, sizeof(captgt));
	if (ret)
		return ret;

	return vfio_info_add_capability(caps, &capspd.header, sizeof(capspd));
}