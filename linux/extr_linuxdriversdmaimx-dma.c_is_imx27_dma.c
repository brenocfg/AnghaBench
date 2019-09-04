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
struct imxdma_engine {scalar_t__ devtype; } ;

/* Variables and functions */
 scalar_t__ IMX27_DMA ; 

__attribute__((used)) static inline int is_imx27_dma(struct imxdma_engine *imxdma)
{
	return imxdma->devtype == IMX27_DMA;
}