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
struct virtqueue {size_t num_free; } ;
struct viommu_event {int dummy; } ;
struct viommu_dev {int /*<<< orphan*/  dev; struct viommu_event* evts; struct virtqueue** vqs; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t VIOMMU_EVENT_VQ ; 
 struct viommu_event* devm_kmalloc_array (int /*<<< orphan*/ ,size_t,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_one (struct scatterlist*,struct viommu_event*,int) ; 
 int virtqueue_add_inbuf (struct virtqueue*,struct scatterlist*,int,struct viommu_event*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int viommu_fill_evtq(struct viommu_dev *viommu)
{
	int i, ret;
	struct scatterlist sg[1];
	struct viommu_event *evts;
	struct virtqueue *vq = viommu->vqs[VIOMMU_EVENT_VQ];
	size_t nr_evts = vq->num_free;

	viommu->evts = evts = devm_kmalloc_array(viommu->dev, nr_evts,
						 sizeof(*evts), GFP_KERNEL);
	if (!evts)
		return -ENOMEM;

	for (i = 0; i < nr_evts; i++) {
		sg_init_one(sg, &evts[i], sizeof(*evts));
		ret = virtqueue_add_inbuf(vq, sg, 1, &evts[i], GFP_KERNEL);
		if (ret)
			return ret;
	}

	return 0;
}