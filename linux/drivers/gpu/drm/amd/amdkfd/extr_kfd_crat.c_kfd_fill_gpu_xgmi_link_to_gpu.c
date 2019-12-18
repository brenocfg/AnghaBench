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
typedef  void* uint32_t ;
struct kfd_dev {int /*<<< orphan*/  kgd; } ;
struct crat_subtype_iolink {int length; int flags; int /*<<< orphan*/  num_hops_xgmi; void* proximity_domain_to; void* proximity_domain_from; int /*<<< orphan*/  io_interface_type; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int CRAT_IOLINK_FLAGS_BI_DIRECTIONAL ; 
 int /*<<< orphan*/  CRAT_IOLINK_TYPE_XGMI ; 
 int CRAT_SUBTYPE_FLAGS_ENABLED ; 
 int /*<<< orphan*/  CRAT_SUBTYPE_IOLINK_AFFINITY ; 
 int ENOMEM ; 
 int /*<<< orphan*/  amdgpu_amdkfd_get_xgmi_hops_count (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int kfd_fill_gpu_xgmi_link_to_gpu(int *avail_size,
			struct kfd_dev *kdev,
			struct kfd_dev *peer_kdev,
			struct crat_subtype_iolink *sub_type_hdr,
			uint32_t proximity_domain_from,
			uint32_t proximity_domain_to)
{
	*avail_size -= sizeof(struct crat_subtype_iolink);
	if (*avail_size < 0)
		return -ENOMEM;

	memset((void *)sub_type_hdr, 0, sizeof(struct crat_subtype_iolink));

	sub_type_hdr->type = CRAT_SUBTYPE_IOLINK_AFFINITY;
	sub_type_hdr->length = sizeof(struct crat_subtype_iolink);
	sub_type_hdr->flags |= CRAT_SUBTYPE_FLAGS_ENABLED |
			       CRAT_IOLINK_FLAGS_BI_DIRECTIONAL;

	sub_type_hdr->io_interface_type = CRAT_IOLINK_TYPE_XGMI;
	sub_type_hdr->proximity_domain_from = proximity_domain_from;
	sub_type_hdr->proximity_domain_to = proximity_domain_to;
	sub_type_hdr->num_hops_xgmi =
		amdgpu_amdkfd_get_xgmi_hops_count(kdev->kgd, peer_kdev->kgd);
	return 0;
}