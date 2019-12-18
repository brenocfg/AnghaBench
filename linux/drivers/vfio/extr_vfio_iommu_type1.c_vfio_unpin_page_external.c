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
struct vfio_pfn {int dummy; } ;
struct vfio_dma {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 struct vfio_pfn* vfio_find_vpfn (struct vfio_dma*,int /*<<< orphan*/ ) ; 
 int vfio_iova_put_vfio_pfn (struct vfio_dma*,struct vfio_pfn*) ; 
 int /*<<< orphan*/  vfio_lock_acct (struct vfio_dma*,int,int) ; 

__attribute__((used)) static int vfio_unpin_page_external(struct vfio_dma *dma, dma_addr_t iova,
				    bool do_accounting)
{
	int unlocked;
	struct vfio_pfn *vpfn = vfio_find_vpfn(dma, iova);

	if (!vpfn)
		return 0;

	unlocked = vfio_iova_put_vfio_pfn(dma, vpfn);

	if (do_accounting)
		vfio_lock_acct(dma, -unlocked, true);

	return unlocked;
}