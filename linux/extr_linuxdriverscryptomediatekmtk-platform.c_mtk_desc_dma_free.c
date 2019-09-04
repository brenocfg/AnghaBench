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
struct mtk_cryp {TYPE_1__** ring; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  cmd_dma; int /*<<< orphan*/  cmd_base; int /*<<< orphan*/  res_dma; int /*<<< orphan*/  res_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTK_DESC_RING_SZ ; 
 int MTK_RING_MAX ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (TYPE_1__*) ; 

__attribute__((used)) static void mtk_desc_dma_free(struct mtk_cryp *cryp)
{
	int i;

	for (i = 0; i < MTK_RING_MAX; i++) {
		dma_free_coherent(cryp->dev, MTK_DESC_RING_SZ,
				  cryp->ring[i]->res_base,
				  cryp->ring[i]->res_dma);
		dma_free_coherent(cryp->dev, MTK_DESC_RING_SZ,
				  cryp->ring[i]->cmd_base,
				  cryp->ring[i]->cmd_dma);
		kfree(cryp->ring[i]);
	}
}