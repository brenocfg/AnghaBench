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
struct idma64 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG ; 
 int /*<<< orphan*/  IDMA64_CFG_DMA_EN ; 
 int /*<<< orphan*/  dma_writel (struct idma64*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void idma64_on(struct idma64 *idma64)
{
	dma_writel(idma64, CFG, IDMA64_CFG_DMA_EN);
}