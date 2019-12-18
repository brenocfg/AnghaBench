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
struct gen_pool {int dummy; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __gp_dma_free_dma ; 
 int /*<<< orphan*/  gen_pool_destroy (struct gen_pool*) ; 
 int /*<<< orphan*/  gen_pool_for_each_chunk (struct gen_pool*,int /*<<< orphan*/ ,struct device*) ; 

void cio_gp_dma_destroy(struct gen_pool *gp_dma, struct device *dma_dev)
{
	if (!gp_dma)
		return;
	/* this is quite ugly but no better idea */
	gen_pool_for_each_chunk(gp_dma, __gp_dma_free_dma, dma_dev);
	gen_pool_destroy(gp_dma);
}