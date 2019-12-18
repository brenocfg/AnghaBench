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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct virtio_iommu_fault {int reason; int /*<<< orphan*/  address; int /*<<< orphan*/  endpoint; int /*<<< orphan*/  flags; } ;
struct viommu_dev {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int VIRTIO_IOMMU_FAULT_F_ADDRESS ; 
 int VIRTIO_IOMMU_FAULT_F_EXEC ; 
 int VIRTIO_IOMMU_FAULT_F_READ ; 
 int VIRTIO_IOMMU_FAULT_F_WRITE ; 
#define  VIRTIO_IOMMU_FAULT_R_DOMAIN 130 
#define  VIRTIO_IOMMU_FAULT_R_MAPPING 129 
#define  VIRTIO_IOMMU_FAULT_R_UNKNOWN 128 
 int /*<<< orphan*/  dev_err_ratelimited (int /*<<< orphan*/ ,char*,char*,int,...) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int viommu_fault_handler(struct viommu_dev *viommu,
				struct virtio_iommu_fault *fault)
{
	char *reason_str;

	u8 reason	= fault->reason;
	u32 flags	= le32_to_cpu(fault->flags);
	u32 endpoint	= le32_to_cpu(fault->endpoint);
	u64 address	= le64_to_cpu(fault->address);

	switch (reason) {
	case VIRTIO_IOMMU_FAULT_R_DOMAIN:
		reason_str = "domain";
		break;
	case VIRTIO_IOMMU_FAULT_R_MAPPING:
		reason_str = "page";
		break;
	case VIRTIO_IOMMU_FAULT_R_UNKNOWN:
	default:
		reason_str = "unknown";
		break;
	}

	/* TODO: find EP by ID and report_iommu_fault */
	if (flags & VIRTIO_IOMMU_FAULT_F_ADDRESS)
		dev_err_ratelimited(viommu->dev, "%s fault from EP %u at %#llx [%s%s%s]\n",
				    reason_str, endpoint, address,
				    flags & VIRTIO_IOMMU_FAULT_F_READ ? "R" : "",
				    flags & VIRTIO_IOMMU_FAULT_F_WRITE ? "W" : "",
				    flags & VIRTIO_IOMMU_FAULT_F_EXEC ? "X" : "");
	else
		dev_err_ratelimited(viommu->dev, "%s fault from EP %u\n",
				    reason_str, endpoint);
	return 0;
}