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
struct TYPE_2__ {int (* dma_read ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CCR ; 
 int OMAP_DMA_CCR_EN ; 
 TYPE_1__* p ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

int omap_get_dma_active_status(int lch)
{
	return (p->dma_read(CCR, lch) & OMAP_DMA_CCR_EN) != 0;
}