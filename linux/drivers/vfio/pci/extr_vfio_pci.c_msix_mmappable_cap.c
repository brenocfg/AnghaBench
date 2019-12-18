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
struct vfio_pci_device {int dummy; } ;
struct vfio_info_cap_header {int version; int /*<<< orphan*/  id; } ;
struct vfio_info_cap {int dummy; } ;
typedef  int /*<<< orphan*/  header ;

/* Variables and functions */
 int /*<<< orphan*/  VFIO_REGION_INFO_CAP_MSIX_MAPPABLE ; 
 int vfio_info_add_capability (struct vfio_info_cap*,struct vfio_info_cap_header*,int) ; 

__attribute__((used)) static int msix_mmappable_cap(struct vfio_pci_device *vdev,
			      struct vfio_info_cap *caps)
{
	struct vfio_info_cap_header header = {
		.id = VFIO_REGION_INFO_CAP_MSIX_MAPPABLE,
		.version = 1
	};

	return vfio_info_add_capability(caps, &header, sizeof(header));
}