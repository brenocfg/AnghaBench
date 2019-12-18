#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int nents; int /*<<< orphan*/  orig_nents; int /*<<< orphan*/  sgl; } ;
struct vmw_ttm_tt {TYPE_3__ sgt; TYPE_2__* dev_priv; } ;
struct device {int dummy; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int ENOMEM ; 
 int dma_map_sg (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int vmw_ttm_map_for_dma(struct vmw_ttm_tt *vmw_tt)
{
	struct device *dev = vmw_tt->dev_priv->dev->dev;
	int ret;

	ret = dma_map_sg(dev, vmw_tt->sgt.sgl, vmw_tt->sgt.orig_nents,
			 DMA_BIDIRECTIONAL);
	if (unlikely(ret == 0))
		return -ENOMEM;

	vmw_tt->sgt.nents = ret;

	return 0;
}