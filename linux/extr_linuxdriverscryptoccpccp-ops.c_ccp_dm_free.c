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
struct TYPE_2__ {scalar_t__ address; int /*<<< orphan*/  dir; } ;
struct ccp_dm_workarea {scalar_t__ length; TYPE_1__ dma; int /*<<< orphan*/ * address; int /*<<< orphan*/  dev; int /*<<< orphan*/  dma_pool; } ;

/* Variables and functions */
 scalar_t__ CCP_DMAPOOL_MAX_SIZE ; 
 int /*<<< orphan*/  dma_pool_free (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ccp_dm_free(struct ccp_dm_workarea *wa)
{
	if (wa->length <= CCP_DMAPOOL_MAX_SIZE) {
		if (wa->address)
			dma_pool_free(wa->dma_pool, wa->address,
				      wa->dma.address);
	} else {
		if (wa->dma.address)
			dma_unmap_single(wa->dev, wa->dma.address, wa->length,
					 wa->dma.dir);
		kfree(wa->address);
	}

	wa->address = NULL;
	wa->dma.address = 0;
}