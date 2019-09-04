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
struct jz4740_dma_sg {int dummy; } ;
struct jz4740_dma_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct jz4740_dma_desc* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct jz4740_dma_desc *jz4740_dma_alloc_desc(unsigned int num_sgs)
{
	return kzalloc(sizeof(struct jz4740_dma_desc) +
		sizeof(struct jz4740_dma_sg) * num_sgs, GFP_ATOMIC);
}