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
struct sec4_sg_entry {int dummy; } ;
struct scatterlist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dma_to_sec4_sg_one (struct sec4_sg_entry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_dma_address (struct scatterlist*) ; 
 int /*<<< orphan*/  sg_dma_len (struct scatterlist*) ; 
 struct scatterlist* sg_next (struct scatterlist*) ; 

__attribute__((used)) static inline struct sec4_sg_entry *
sg_to_sec4_sg(struct scatterlist *sg, int sg_count,
	      struct sec4_sg_entry *sec4_sg_ptr, u16 offset)
{
	while (sg_count) {
		dma_to_sec4_sg_one(sec4_sg_ptr, sg_dma_address(sg),
				   sg_dma_len(sg), offset);
		sec4_sg_ptr++;
		sg = sg_next(sg);
		sg_count--;
	}
	return sec4_sg_ptr - 1;
}