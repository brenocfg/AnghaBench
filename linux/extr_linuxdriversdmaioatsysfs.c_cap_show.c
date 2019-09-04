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
struct dma_device {int /*<<< orphan*/  cap_mask; } ;
struct dma_chan {struct dma_device* device; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_INTERRUPT ; 
 int /*<<< orphan*/  DMA_PQ ; 
 int /*<<< orphan*/  DMA_PQ_VAL ; 
 int /*<<< orphan*/  DMA_XOR ; 
 int /*<<< orphan*/  DMA_XOR_VAL ; 
 scalar_t__ dma_has_cap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static ssize_t cap_show(struct dma_chan *c, char *page)
{
	struct dma_device *dma = c->device;

	return sprintf(page, "copy%s%s%s%s%s\n",
		       dma_has_cap(DMA_PQ, dma->cap_mask) ? " pq" : "",
		       dma_has_cap(DMA_PQ_VAL, dma->cap_mask) ? " pq_val" : "",
		       dma_has_cap(DMA_XOR, dma->cap_mask) ? " xor" : "",
		       dma_has_cap(DMA_XOR_VAL, dma->cap_mask) ? " xor_val" : "",
		       dma_has_cap(DMA_INTERRUPT, dma->cap_mask) ? " intr" : "");

}