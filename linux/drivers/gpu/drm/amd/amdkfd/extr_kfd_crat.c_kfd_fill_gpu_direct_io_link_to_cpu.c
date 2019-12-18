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
typedef  int /*<<< orphan*/  uint32_t ;
struct kfd_dev {TYPE_2__* pdev; } ;
struct crat_subtype_iolink {int length; scalar_t__ proximity_domain_to; int /*<<< orphan*/  proximity_domain_from; int /*<<< orphan*/  io_interface_type; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {scalar_t__ numa_node; } ;
struct TYPE_4__ {TYPE_1__ dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRAT_IOLINK_FLAGS_BI_DIRECTIONAL ; 
 int /*<<< orphan*/  CRAT_IOLINK_TYPE_PCIEXPRESS ; 
 int /*<<< orphan*/  CRAT_SUBTYPE_FLAGS_ENABLED ; 
 int /*<<< orphan*/  CRAT_SUBTYPE_IOLINK_AFFINITY ; 
 int ENOMEM ; 
 scalar_t__ NUMA_NO_NODE ; 
 scalar_t__ kfd_dev_is_large_bar (struct kfd_dev*) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int kfd_fill_gpu_direct_io_link_to_cpu(int *avail_size,
			struct kfd_dev *kdev,
			struct crat_subtype_iolink *sub_type_hdr,
			uint32_t proximity_domain)
{
	*avail_size -= sizeof(struct crat_subtype_iolink);
	if (*avail_size < 0)
		return -ENOMEM;

	memset((void *)sub_type_hdr, 0, sizeof(struct crat_subtype_iolink));

	/* Fill in subtype header data */
	sub_type_hdr->type = CRAT_SUBTYPE_IOLINK_AFFINITY;
	sub_type_hdr->length = sizeof(struct crat_subtype_iolink);
	sub_type_hdr->flags |= CRAT_SUBTYPE_FLAGS_ENABLED;
	if (kfd_dev_is_large_bar(kdev))
		sub_type_hdr->flags |= CRAT_IOLINK_FLAGS_BI_DIRECTIONAL;

	/* Fill in IOLINK subtype.
	 * TODO: Fill-in other fields of iolink subtype
	 */
	sub_type_hdr->io_interface_type = CRAT_IOLINK_TYPE_PCIEXPRESS;
	sub_type_hdr->proximity_domain_from = proximity_domain;
#ifdef CONFIG_NUMA
	if (kdev->pdev->dev.numa_node == NUMA_NO_NODE)
		sub_type_hdr->proximity_domain_to = 0;
	else
		sub_type_hdr->proximity_domain_to = kdev->pdev->dev.numa_node;
#else
	sub_type_hdr->proximity_domain_to = 0;
#endif
	return 0;
}