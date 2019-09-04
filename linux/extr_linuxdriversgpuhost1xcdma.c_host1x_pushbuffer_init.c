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
typedef  unsigned long u32 ;
struct push_buffer {int size; int fence; unsigned long alloc_size; int /*<<< orphan*/  phys; int /*<<< orphan*/ * mapped; int /*<<< orphan*/  dma; scalar_t__ pos; } ;
struct iova {int dummy; } ;
struct host1x_cdma {int dummy; } ;
struct host1x {unsigned long iova_end; int /*<<< orphan*/  dev; int /*<<< orphan*/  iova; scalar_t__ domain; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HOST1X_PUSHBUFFER_SLOTS ; 
 int /*<<< orphan*/  IOMMU_READ ; 
 int /*<<< orphan*/  __free_iova (int /*<<< orphan*/ *,struct iova*) ; 
 struct iova* alloc_iova (int /*<<< orphan*/ *,unsigned long,unsigned long,int) ; 
 struct host1x* cdma_to_host1x (struct host1x_cdma*) ; 
 void* dma_alloc_wc (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_wc (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_hw_pushbuffer_init (struct host1x*,struct push_buffer*) ; 
 int iommu_map (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long iova_align (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  iova_dma_addr (int /*<<< orphan*/ *,struct iova*) ; 
 unsigned long iova_shift (int /*<<< orphan*/ *) ; 
 struct host1x_cdma* pb_to_cdma (struct push_buffer*) ; 

__attribute__((used)) static int host1x_pushbuffer_init(struct push_buffer *pb)
{
	struct host1x_cdma *cdma = pb_to_cdma(pb);
	struct host1x *host1x = cdma_to_host1x(cdma);
	struct iova *alloc;
	u32 size;
	int err;

	pb->mapped = NULL;
	pb->phys = 0;
	pb->size = HOST1X_PUSHBUFFER_SLOTS * 8;

	size = pb->size + 4;

	/* initialize buffer pointers */
	pb->fence = pb->size - 8;
	pb->pos = 0;

	if (host1x->domain) {
		unsigned long shift;

		size = iova_align(&host1x->iova, size);

		pb->mapped = dma_alloc_wc(host1x->dev, size, &pb->phys,
					  GFP_KERNEL);
		if (!pb->mapped)
			return -ENOMEM;

		shift = iova_shift(&host1x->iova);
		alloc = alloc_iova(&host1x->iova, size >> shift,
				   host1x->iova_end >> shift, true);
		if (!alloc) {
			err = -ENOMEM;
			goto iommu_free_mem;
		}

		pb->dma = iova_dma_addr(&host1x->iova, alloc);
		err = iommu_map(host1x->domain, pb->dma, pb->phys, size,
				IOMMU_READ);
		if (err)
			goto iommu_free_iova;
	} else {
		pb->mapped = dma_alloc_wc(host1x->dev, size, &pb->phys,
					  GFP_KERNEL);
		if (!pb->mapped)
			return -ENOMEM;

		pb->dma = pb->phys;
	}

	pb->alloc_size = size;

	host1x_hw_pushbuffer_init(host1x, pb);

	return 0;

iommu_free_iova:
	__free_iova(&host1x->iova, alloc);
iommu_free_mem:
	dma_free_wc(host1x->dev, size, pb->mapped, pb->phys);

	return err;
}