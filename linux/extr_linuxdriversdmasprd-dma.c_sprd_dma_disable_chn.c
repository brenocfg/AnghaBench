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
struct sprd_dma_chn {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPRD_DMA_CHN_CFG ; 
 int /*<<< orphan*/  SPRD_DMA_CHN_EN ; 
 int /*<<< orphan*/  sprd_dma_chn_update (struct sprd_dma_chn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sprd_dma_disable_chn(struct sprd_dma_chn *schan)
{
	sprd_dma_chn_update(schan, SPRD_DMA_CHN_CFG, SPRD_DMA_CHN_EN, 0);
}