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
typedef  int u32 ;
struct sprd_dma_chn {int chn_base; } ;

/* Variables and functions */
 int readl (int) ; 
 int /*<<< orphan*/  writel (int,int) ; 

__attribute__((used)) static void sprd_dma_chn_update(struct sprd_dma_chn *schan, u32 reg,
				u32 mask, u32 val)
{
	u32 orig = readl(schan->chn_base + reg);
	u32 tmp;

	tmp = (orig & ~mask) | val;
	writel(tmp, schan->chn_base + reg);
}