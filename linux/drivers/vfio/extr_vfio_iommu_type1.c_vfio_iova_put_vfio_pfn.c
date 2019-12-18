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
struct vfio_pfn {int /*<<< orphan*/  pfn; int /*<<< orphan*/  ref_count; } ;
struct vfio_dma {int /*<<< orphan*/  prot; } ;

/* Variables and functions */
 scalar_t__ atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int put_pfn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfio_remove_from_pfn_list (struct vfio_dma*,struct vfio_pfn*) ; 

__attribute__((used)) static int vfio_iova_put_vfio_pfn(struct vfio_dma *dma, struct vfio_pfn *vpfn)
{
	int ret = 0;

	if (atomic_dec_and_test(&vpfn->ref_count)) {
		ret = put_pfn(vpfn->pfn, dma->prot);
		vfio_remove_from_pfn_list(dma, vpfn);
	}
	return ret;
}