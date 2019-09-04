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
struct mv_cesa_sg_dma_iter {scalar_t__ offset; int /*<<< orphan*/  sg; scalar_t__ op_offset; } ;
struct mv_cesa_dma_iter {scalar_t__ op_len; } ;

/* Variables and functions */
 unsigned int min (scalar_t__,scalar_t__) ; 
 scalar_t__ sg_dma_len (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline unsigned int
mv_cesa_req_dma_iter_transfer_len(struct mv_cesa_dma_iter *iter,
				  struct mv_cesa_sg_dma_iter *sgiter)
{
	return min(iter->op_len - sgiter->op_offset,
		   sg_dma_len(sgiter->sg) - sgiter->offset);
}