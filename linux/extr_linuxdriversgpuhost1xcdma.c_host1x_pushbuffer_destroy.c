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
struct push_buffer {int /*<<< orphan*/  phys; int /*<<< orphan*/ * mapped; int /*<<< orphan*/  alloc_size; int /*<<< orphan*/  dma; } ;
struct host1x_cdma {int dummy; } ;
struct host1x {int /*<<< orphan*/  dev; int /*<<< orphan*/  iova; scalar_t__ domain; } ;

/* Variables and functions */
 struct host1x* cdma_to_host1x (struct host1x_cdma*) ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_iova (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_unmap (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iova_pfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct host1x_cdma* pb_to_cdma (struct push_buffer*) ; 

__attribute__((used)) static void host1x_pushbuffer_destroy(struct push_buffer *pb)
{
	struct host1x_cdma *cdma = pb_to_cdma(pb);
	struct host1x *host1x = cdma_to_host1x(cdma);

	if (!pb->mapped)
		return;

	if (host1x->domain) {
		iommu_unmap(host1x->domain, pb->dma, pb->alloc_size);
		free_iova(&host1x->iova, iova_pfn(&host1x->iova, pb->dma));
	}

	dma_free_wc(host1x->dev, pb->alloc_size, pb->mapped, pb->phys);

	pb->mapped = NULL;
	pb->phys = 0;
}