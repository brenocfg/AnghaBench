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
struct cnic_local {int ctx_blks; TYPE_2__* ctx_arr; int /*<<< orphan*/  ctx_blk_size; } ;
struct cnic_dev {TYPE_1__* pcidev; struct cnic_local* cnic_priv; } ;
struct TYPE_4__ {int /*<<< orphan*/ * ctx; int /*<<< orphan*/  mapping; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cnic_free_context(struct cnic_dev *dev)
{
	struct cnic_local *cp = dev->cnic_priv;
	int i;

	for (i = 0; i < cp->ctx_blks; i++) {
		if (cp->ctx_arr[i].ctx) {
			dma_free_coherent(&dev->pcidev->dev, cp->ctx_blk_size,
					  cp->ctx_arr[i].ctx,
					  cp->ctx_arr[i].mapping);
			cp->ctx_arr[i].ctx = NULL;
		}
	}
}