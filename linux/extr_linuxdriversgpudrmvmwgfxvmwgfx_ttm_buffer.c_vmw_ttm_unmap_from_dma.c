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
struct TYPE_6__ {int /*<<< orphan*/  orig_nents; int /*<<< orphan*/  nents; int /*<<< orphan*/  sgl; } ;
struct vmw_ttm_tt {TYPE_3__ sgt; TYPE_2__* dev_priv; } ;
struct device {int dummy; } ;
struct TYPE_5__ {TYPE_1__* dev; } ;
struct TYPE_4__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  dma_unmap_sg (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vmw_ttm_unmap_from_dma(struct vmw_ttm_tt *vmw_tt)
{
	struct device *dev = vmw_tt->dev_priv->dev->dev;

	dma_unmap_sg(dev, vmw_tt->sgt.sgl, vmw_tt->sgt.nents,
		DMA_BIDIRECTIONAL);
	vmw_tt->sgt.nents = vmw_tt->sgt.orig_nents;
}