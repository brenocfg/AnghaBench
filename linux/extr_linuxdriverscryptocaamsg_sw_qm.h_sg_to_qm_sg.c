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
typedef  int /*<<< orphan*/  u16 ;
struct scatterlist {int dummy; } ;
struct qm_sg_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_to_qm_sg_one (struct qm_sg_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_dma_len (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static inline struct qm_sg_entry *
sg_to_qm_sg(struct scatterlist *sg, int sg_count,
	    struct qm_sg_entry *qm_sg_ptr, u16 offset)
{
	while (sg_count && sg) {
		dma_to_qm_sg_one(qm_sg_ptr, sg_dma_address(sg),
				 sg_dma_len(sg), offset);
		qm_sg_ptr++;
		sg = sg_next(sg);
		sg_count--;
	}
	return qm_sg_ptr - 1;
}