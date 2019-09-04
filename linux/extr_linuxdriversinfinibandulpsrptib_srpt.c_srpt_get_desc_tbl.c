#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct TYPE_3__ {int data_direction; } ;
struct srpt_send_ioctx {TYPE_1__ cmd; } ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
struct srp_indirect_buf {struct srp_direct_buf* desc_list; int /*<<< orphan*/  len; TYPE_2__ table_desc; } ;
struct srp_direct_buf {int /*<<< orphan*/  len; } ;
struct srp_cmd {int buf_fmt; int data_out_desc_cnt; int data_in_desc_cnt; } ;
struct scatterlist {int dummy; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DMA_FROM_DEVICE ; 
 int DMA_NONE ; 
 int DMA_TO_DEVICE ; 
 int EINVAL ; 
 int SRP_DATA_DESC_DIRECT ; 
 int SRP_DATA_DESC_INDIRECT ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,int,int,int) ; 
 int srpt_alloc_rw_ctxs (struct srpt_send_ioctx*,struct srp_direct_buf*,int,struct scatterlist**,unsigned int*) ; 
 void* srpt_get_desc_buf (struct srp_cmd*) ; 

__attribute__((used)) static int srpt_get_desc_tbl(struct srpt_send_ioctx *ioctx,
		struct srp_cmd *srp_cmd, enum dma_data_direction *dir,
		struct scatterlist **sg, unsigned *sg_cnt, u64 *data_len)
{
	BUG_ON(!dir);
	BUG_ON(!data_len);

	/*
	 * The lower four bits of the buffer format field contain the DATA-IN
	 * buffer descriptor format, and the highest four bits contain the
	 * DATA-OUT buffer descriptor format.
	 */
	if (srp_cmd->buf_fmt & 0xf)
		/* DATA-IN: transfer data from target to initiator (read). */
		*dir = DMA_FROM_DEVICE;
	else if (srp_cmd->buf_fmt >> 4)
		/* DATA-OUT: transfer data from initiator to target (write). */
		*dir = DMA_TO_DEVICE;
	else
		*dir = DMA_NONE;

	/* initialize data_direction early as srpt_alloc_rw_ctxs needs it */
	ioctx->cmd.data_direction = *dir;

	if (((srp_cmd->buf_fmt & 0xf) == SRP_DATA_DESC_DIRECT) ||
	    ((srp_cmd->buf_fmt >> 4) == SRP_DATA_DESC_DIRECT)) {
	    	struct srp_direct_buf *db = srpt_get_desc_buf(srp_cmd);

		*data_len = be32_to_cpu(db->len);
		return srpt_alloc_rw_ctxs(ioctx, db, 1, sg, sg_cnt);
	} else if (((srp_cmd->buf_fmt & 0xf) == SRP_DATA_DESC_INDIRECT) ||
		   ((srp_cmd->buf_fmt >> 4) == SRP_DATA_DESC_INDIRECT)) {
		struct srp_indirect_buf *idb = srpt_get_desc_buf(srp_cmd);
		int nbufs = be32_to_cpu(idb->table_desc.len) /
				sizeof(struct srp_direct_buf);

		if (nbufs >
		    (srp_cmd->data_out_desc_cnt + srp_cmd->data_in_desc_cnt)) {
			pr_err("received unsupported SRP_CMD request"
			       " type (%u out + %u in != %u / %zu)\n",
			       srp_cmd->data_out_desc_cnt,
			       srp_cmd->data_in_desc_cnt,
			       be32_to_cpu(idb->table_desc.len),
			       sizeof(struct srp_direct_buf));
			return -EINVAL;
		}

		*data_len = be32_to_cpu(idb->len);
		return srpt_alloc_rw_ctxs(ioctx, idb->desc_list, nbufs,
				sg, sg_cnt);
	} else {
		*data_len = 0;
		return 0;
	}
}