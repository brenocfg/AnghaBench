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
struct vfio_pfn {unsigned long pfn; int /*<<< orphan*/  ref_count; int /*<<< orphan*/  iova; } ;
struct vfio_dma {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 struct vfio_pfn* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_link_pfn (struct vfio_dma*,struct vfio_pfn*) ; 

__attribute__((used)) static int vfio_add_to_pfn_list(struct vfio_dma *dma, dma_addr_t iova,
				unsigned long pfn)
{
	struct vfio_pfn *vpfn;

	vpfn = kzalloc(sizeof(*vpfn), GFP_KERNEL);
	if (!vpfn)
		return -ENOMEM;

	vpfn->iova = iova;
	vpfn->pfn = pfn;
	atomic_set(&vpfn->ref_count, 1);
	vfio_link_pfn(dma, vpfn);
	return 0;
}