#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {unsigned int offset; unsigned int length; void* address; } ;
struct TYPE_16__ {TYPE_6__ dma; } ;
struct TYPE_17__ {TYPE_7__ u; } ;
struct TYPE_12__ {unsigned int offset; unsigned int length; void* address; } ;
struct TYPE_13__ {TYPE_3__ dma; } ;
struct TYPE_14__ {TYPE_4__ u; } ;
struct ccp_op {int soc; TYPE_8__ src; TYPE_5__ dst; } ;
struct TYPE_18__ {unsigned int sg_used; int /*<<< orphan*/  sg; int /*<<< orphan*/  bytes_left; } ;
struct TYPE_10__ {void* address; } ;
struct TYPE_11__ {TYPE_1__ dma; } ;
struct ccp_data {TYPE_9__ sg_wa; TYPE_2__ dm_wa; } ;

/* Variables and functions */
 int ccp_fill_queue_buf (struct ccp_data*) ; 
 int /*<<< orphan*/  ccp_update_sg_workarea (TYPE_9__*,unsigned int) ; 
 unsigned int max (unsigned int,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 unsigned int min_t (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 void* sg_dma_address (int /*<<< orphan*/ ) ; 
 unsigned int sg_dma_len (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  u64 ; 

__attribute__((used)) static void ccp_prepare_data(struct ccp_data *src, struct ccp_data *dst,
			     struct ccp_op *op, unsigned int block_size,
			     bool blocksize_op)
{
	unsigned int sg_src_len, sg_dst_len, op_len;

	/* The CCP can only DMA from/to one address each per operation. This
	 * requires that we find the smallest DMA area between the source
	 * and destination. The resulting len values will always be <= UINT_MAX
	 * because the dma length is an unsigned int.
	 */
	sg_src_len = sg_dma_len(src->sg_wa.sg) - src->sg_wa.sg_used;
	sg_src_len = min_t(u64, src->sg_wa.bytes_left, sg_src_len);

	if (dst) {
		sg_dst_len = sg_dma_len(dst->sg_wa.sg) - dst->sg_wa.sg_used;
		sg_dst_len = min_t(u64, src->sg_wa.bytes_left, sg_dst_len);
		op_len = min(sg_src_len, sg_dst_len);
	} else {
		op_len = sg_src_len;
	}

	/* The data operation length will be at least block_size in length
	 * or the smaller of available sg room remaining for the source or
	 * the destination
	 */
	op_len = max(op_len, block_size);

	/* Unless we have to buffer data, there's no reason to wait */
	op->soc = 0;

	if (sg_src_len < block_size) {
		/* Not enough data in the sg element, so it
		 * needs to be buffered into a blocksize chunk
		 */
		int cp_len = ccp_fill_queue_buf(src);

		op->soc = 1;
		op->src.u.dma.address = src->dm_wa.dma.address;
		op->src.u.dma.offset = 0;
		op->src.u.dma.length = (blocksize_op) ? block_size : cp_len;
	} else {
		/* Enough data in the sg element, but we need to
		 * adjust for any previously copied data
		 */
		op->src.u.dma.address = sg_dma_address(src->sg_wa.sg);
		op->src.u.dma.offset = src->sg_wa.sg_used;
		op->src.u.dma.length = op_len & ~(block_size - 1);

		ccp_update_sg_workarea(&src->sg_wa, op->src.u.dma.length);
	}

	if (dst) {
		if (sg_dst_len < block_size) {
			/* Not enough room in the sg element or we're on the
			 * last piece of data (when using padding), so the
			 * output needs to be buffered into a blocksize chunk
			 */
			op->soc = 1;
			op->dst.u.dma.address = dst->dm_wa.dma.address;
			op->dst.u.dma.offset = 0;
			op->dst.u.dma.length = op->src.u.dma.length;
		} else {
			/* Enough room in the sg element, but we need to
			 * adjust for any previously used area
			 */
			op->dst.u.dma.address = sg_dma_address(dst->sg_wa.sg);
			op->dst.u.dma.offset = dst->sg_wa.sg_used;
			op->dst.u.dma.length = op->src.u.dma.length;
		}
	}
}