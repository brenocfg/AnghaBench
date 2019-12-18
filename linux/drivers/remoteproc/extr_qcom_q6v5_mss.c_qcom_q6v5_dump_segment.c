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
struct rproc_dump_segment {int /*<<< orphan*/  size; int /*<<< orphan*/  da; scalar_t__ priv; } ;
struct rproc {struct q6v5* priv; } ;
struct q6v5 {unsigned long dump_segment_mask; unsigned long dump_complete_mask; scalar_t__ dump_mba_loaded; } ;

/* Variables and functions */
 unsigned long BIT (unsigned long) ; 
 int /*<<< orphan*/  memcpy (void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int,int /*<<< orphan*/ ) ; 
 int q6v5_mba_load (struct q6v5*) ; 
 int /*<<< orphan*/  q6v5_mba_reclaim (struct q6v5*) ; 
 void* rproc_da_to_va (struct rproc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qcom_q6v5_dump_segment(struct rproc *rproc,
				   struct rproc_dump_segment *segment,
				   void *dest)
{
	int ret = 0;
	struct q6v5 *qproc = rproc->priv;
	unsigned long mask = BIT((unsigned long)segment->priv);
	void *ptr = rproc_da_to_va(rproc, segment->da, segment->size);

	/* Unlock mba before copying segments */
	if (!qproc->dump_mba_loaded)
		ret = q6v5_mba_load(qproc);

	if (!ptr || ret)
		memset(dest, 0xff, segment->size);
	else
		memcpy(dest, ptr, segment->size);

	qproc->dump_segment_mask |= mask;

	/* Reclaim mba after copying segments */
	if (qproc->dump_segment_mask == qproc->dump_complete_mask) {
		if (qproc->dump_mba_loaded)
			q6v5_mba_reclaim(qproc);
	}
}