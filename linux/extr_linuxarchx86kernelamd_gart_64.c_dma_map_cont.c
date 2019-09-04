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
struct scatterlist {int /*<<< orphan*/  length; int /*<<< orphan*/  dma_length; int /*<<< orphan*/  dma_address; } ;
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int __dma_map_cont (struct device*,struct scatterlist*,int,struct scatterlist*,unsigned long) ; 

__attribute__((used)) static inline int
dma_map_cont(struct device *dev, struct scatterlist *start, int nelems,
	     struct scatterlist *sout, unsigned long pages, int need)
{
	if (!need) {
		BUG_ON(nelems != 1);
		sout->dma_address = start->dma_address;
		sout->dma_length = start->length;
		return 0;
	}
	return __dma_map_cont(dev, start, nelems, sout, pages);
}