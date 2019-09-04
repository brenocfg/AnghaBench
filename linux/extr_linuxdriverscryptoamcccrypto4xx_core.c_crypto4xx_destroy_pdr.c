#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  union shadow_sa_buf {int dummy; } shadow_sa_buf ;
struct sa_state_record {int dummy; } ;
struct crypto4xx_device {int /*<<< orphan*/  pdr_uinfo; int /*<<< orphan*/  shadow_sr_pool_pa; scalar_t__ shadow_sr_pool; TYPE_1__* core_dev; int /*<<< orphan*/  shadow_sa_pool_pa; scalar_t__ shadow_sa_pool; int /*<<< orphan*/  pdr_pa; scalar_t__ pdr; } ;
struct ce_pd {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int PPC4XX_NUM_PD ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void crypto4xx_destroy_pdr(struct crypto4xx_device *dev)
{
	if (dev->pdr)
		dma_free_coherent(dev->core_dev->device,
				  sizeof(struct ce_pd) * PPC4XX_NUM_PD,
				  dev->pdr, dev->pdr_pa);

	if (dev->shadow_sa_pool)
		dma_free_coherent(dev->core_dev->device,
			sizeof(union shadow_sa_buf) * PPC4XX_NUM_PD,
			dev->shadow_sa_pool, dev->shadow_sa_pool_pa);

	if (dev->shadow_sr_pool)
		dma_free_coherent(dev->core_dev->device,
			sizeof(struct sa_state_record) * PPC4XX_NUM_PD,
			dev->shadow_sr_pool, dev->shadow_sr_pool_pa);

	kfree(dev->pdr_uinfo);
}