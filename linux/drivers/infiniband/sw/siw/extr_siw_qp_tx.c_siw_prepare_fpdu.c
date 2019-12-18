#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_9__ {int raddr; } ;
struct siw_wqe {int processed; int bytes; TYPE_3__ sqe; } ;
struct TYPE_12__ {int ddp_rdmap_ctrl; int /*<<< orphan*/  mpa_len; } ;
struct TYPE_8__ {int /*<<< orphan*/  ddp_to; } ;
struct TYPE_7__ {int /*<<< orphan*/  ddp_mo; } ;
struct TYPE_10__ {TYPE_6__ ctrl; TYPE_2__ c_tagged; TYPE_1__ c_untagged; } ;
struct siw_iwarp_tx {scalar_t__ ctrl_len; scalar_t__ tcp_seglen; int pad; int bytes_unsent; int do_crc; TYPE_4__ pkt; scalar_t__ mpa_crc_hd; scalar_t__ ctrl_sent; } ;
struct siw_qp {struct siw_iwarp_tx tx_ctx; } ;
struct TYPE_11__ {scalar_t__ hdr_len; } ;

/* Variables and functions */
 int DDP_FLAG_LAST ; 
 int DDP_FLAG_TAGGED ; 
 scalar_t__ MPA_CRC_SIZE ; 
 scalar_t__ MPA_HDR_SIZE ; 
 size_t __rdmap_get_opcode (TYPE_6__*) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int) ; 
 int /*<<< orphan*/  crypto_shash_init (scalar_t__) ; 
 int /*<<< orphan*/  crypto_shash_update (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 TYPE_5__* iwarp_pktinfo ; 

__attribute__((used)) static void siw_prepare_fpdu(struct siw_qp *qp, struct siw_wqe *wqe)
{
	struct siw_iwarp_tx *c_tx = &qp->tx_ctx;
	int data_len;

	c_tx->ctrl_len =
		iwarp_pktinfo[__rdmap_get_opcode(&c_tx->pkt.ctrl)].hdr_len;
	c_tx->ctrl_sent = 0;

	/*
	 * Update target buffer offset if any
	 */
	if (!(c_tx->pkt.ctrl.ddp_rdmap_ctrl & DDP_FLAG_TAGGED))
		/* Untagged message */
		c_tx->pkt.c_untagged.ddp_mo = cpu_to_be32(wqe->processed);
	else /* Tagged message */
		c_tx->pkt.c_tagged.ddp_to =
			cpu_to_be64(wqe->sqe.raddr + wqe->processed);

	data_len = wqe->bytes - wqe->processed;
	if (data_len + c_tx->ctrl_len + MPA_CRC_SIZE > c_tx->tcp_seglen) {
		/* Trim DDP payload to fit into current TCP segment */
		data_len = c_tx->tcp_seglen - (c_tx->ctrl_len + MPA_CRC_SIZE);
		c_tx->pkt.ctrl.ddp_rdmap_ctrl &= ~DDP_FLAG_LAST;
		c_tx->pad = 0;
	} else {
		c_tx->pkt.ctrl.ddp_rdmap_ctrl |= DDP_FLAG_LAST;
		c_tx->pad = -data_len & 0x3;
	}
	c_tx->bytes_unsent = data_len;

	c_tx->pkt.ctrl.mpa_len =
		htons(c_tx->ctrl_len + data_len - MPA_HDR_SIZE);

	/*
	 * Init MPA CRC computation
	 */
	if (c_tx->mpa_crc_hd) {
		crypto_shash_init(c_tx->mpa_crc_hd);
		crypto_shash_update(c_tx->mpa_crc_hd, (u8 *)&c_tx->pkt,
				    c_tx->ctrl_len);
		c_tx->do_crc = 1;
	}
}