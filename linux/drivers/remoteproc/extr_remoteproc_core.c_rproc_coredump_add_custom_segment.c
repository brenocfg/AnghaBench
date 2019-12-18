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
struct rproc_dump_segment {size_t size; void (* dump ) (struct rproc*,struct rproc_dump_segment*,void*) ;int /*<<< orphan*/  node; void* priv; int /*<<< orphan*/  da; } ;
struct rproc {int /*<<< orphan*/  dump_segments; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct rproc_dump_segment* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int rproc_coredump_add_custom_segment(struct rproc *rproc,
				      dma_addr_t da, size_t size,
				      void (*dumpfn)(struct rproc *rproc,
						     struct rproc_dump_segment *segment,
						     void *dest),
				      void *priv)
{
	struct rproc_dump_segment *segment;

	segment = kzalloc(sizeof(*segment), GFP_KERNEL);
	if (!segment)
		return -ENOMEM;

	segment->da = da;
	segment->size = size;
	segment->priv = priv;
	segment->dump = dumpfn;

	list_add_tail(&segment->node, &rproc->dump_segments);

	return 0;
}