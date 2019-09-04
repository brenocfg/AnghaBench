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
struct host1x_job_unpin_data {int /*<<< orphan*/  bo; int /*<<< orphan*/  sgt; scalar_t__ size; } ;
struct host1x_job {unsigned int num_unpins; int /*<<< orphan*/  gather_copy; int /*<<< orphan*/  gather_copy_mapped; scalar_t__ gather_copy_size; TYPE_1__* channel; int /*<<< orphan*/ * addr_phys; struct host1x_job_unpin_data* unpins; } ;
struct host1x {int /*<<< orphan*/  iova; scalar_t__ domain; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_3__ {TYPE_2__* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_TEGRA_HOST1X_FIREWALL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 struct host1x* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_wc (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_iova (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_bo_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host1x_bo_unpin (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iommu_unmap (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  iova_pfn (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void host1x_job_unpin(struct host1x_job *job)
{
	struct host1x *host = dev_get_drvdata(job->channel->dev->parent);
	unsigned int i;

	for (i = 0; i < job->num_unpins; i++) {
		struct host1x_job_unpin_data *unpin = &job->unpins[i];

		if (!IS_ENABLED(CONFIG_TEGRA_HOST1X_FIREWALL) &&
		    unpin->size && host->domain) {
			iommu_unmap(host->domain, job->addr_phys[i],
				    unpin->size);
			free_iova(&host->iova,
				iova_pfn(&host->iova, job->addr_phys[i]));
		}

		host1x_bo_unpin(unpin->bo, unpin->sgt);
		host1x_bo_put(unpin->bo);
	}

	job->num_unpins = 0;

	if (job->gather_copy_size)
		dma_free_wc(job->channel->dev, job->gather_copy_size,
			    job->gather_copy_mapped, job->gather_copy);
}