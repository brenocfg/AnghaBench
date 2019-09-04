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
typedef  size_t u16 ;
struct xdp_frame {unsigned int len; int /*<<< orphan*/  data; } ;
struct mlx5e_xdpsq_stats {int /*<<< orphan*/  xmit; int /*<<< orphan*/  full; int /*<<< orphan*/  err; } ;
struct TYPE_4__ {struct mlx5e_xdp_info* xdpi; } ;
struct mlx5_wq_cyc {int dummy; } ;
struct mlx5e_xdpsq {int pc; unsigned int hw_mtu; int doorbell; scalar_t__ min_inline_mode; TYPE_2__ db; int /*<<< orphan*/  cc; struct mlx5e_xdpsq_stats* stats; struct mlx5_wq_cyc wq; } ;
struct mlx5e_xdp_info {unsigned int dma_addr; struct xdp_frame* xdpf; } ;
struct TYPE_3__ {int /*<<< orphan*/  sz; int /*<<< orphan*/  start; } ;
struct mlx5_wqe_eth_seg {TYPE_1__ inline_hdr; } ;
struct mlx5_wqe_ctrl_seg {void* opmod_idx_opcode; scalar_t__ fm_ce_se; } ;
struct mlx5e_tx_wqe {struct mlx5_wqe_data_seg* data; struct mlx5_wqe_eth_seg eth; struct mlx5_wqe_ctrl_seg ctrl; } ;
struct mlx5_wqe_data_seg {void* byte_count; int /*<<< orphan*/  addr; } ;
typedef  unsigned int dma_addr_t ;

/* Variables and functions */
 unsigned int MLX5E_XDP_MIN_INLINE ; 
 scalar_t__ MLX5_INLINE_MODE_NONE ; 
 int MLX5_OPCODE_SEND ; 
 int /*<<< orphan*/  cpu_to_be16 (unsigned int) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (unsigned int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 size_t mlx5_wq_cyc_ctr2ix (struct mlx5_wq_cyc*,int) ; 
 struct mlx5e_tx_wqe* mlx5_wq_cyc_get_wqe (struct mlx5_wq_cyc*,size_t) ; 
 int /*<<< orphan*/  mlx5e_wqc_has_room_for (struct mlx5_wq_cyc*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  mlx5e_xmit_xdp_doorbell (struct mlx5e_xdpsq*) ; 
 int /*<<< orphan*/  prefetchw (struct mlx5e_tx_wqe*) ; 
 scalar_t__ unlikely (int) ; 

bool mlx5e_xmit_xdp_frame(struct mlx5e_xdpsq *sq, struct mlx5e_xdp_info *xdpi)
{
	struct mlx5_wq_cyc       *wq   = &sq->wq;
	u16                       pi   = mlx5_wq_cyc_ctr2ix(wq, sq->pc);
	struct mlx5e_tx_wqe      *wqe  = mlx5_wq_cyc_get_wqe(wq, pi);

	struct mlx5_wqe_ctrl_seg *cseg = &wqe->ctrl;
	struct mlx5_wqe_eth_seg  *eseg = &wqe->eth;
	struct mlx5_wqe_data_seg *dseg = wqe->data;

	struct xdp_frame *xdpf = xdpi->xdpf;
	dma_addr_t dma_addr  = xdpi->dma_addr;
	unsigned int dma_len = xdpf->len;

	struct mlx5e_xdpsq_stats *stats = sq->stats;

	prefetchw(wqe);

	if (unlikely(dma_len < MLX5E_XDP_MIN_INLINE || sq->hw_mtu < dma_len)) {
		stats->err++;
		return false;
	}

	if (unlikely(!mlx5e_wqc_has_room_for(wq, sq->cc, sq->pc, 1))) {
		if (sq->doorbell) {
			/* SQ is full, ring doorbell */
			mlx5e_xmit_xdp_doorbell(sq);
			sq->doorbell = false;
		}
		stats->full++;
		return false;
	}

	cseg->fm_ce_se = 0;

	/* copy the inline part if required */
	if (sq->min_inline_mode != MLX5_INLINE_MODE_NONE) {
		memcpy(eseg->inline_hdr.start, xdpf->data, MLX5E_XDP_MIN_INLINE);
		eseg->inline_hdr.sz = cpu_to_be16(MLX5E_XDP_MIN_INLINE);
		dma_len  -= MLX5E_XDP_MIN_INLINE;
		dma_addr += MLX5E_XDP_MIN_INLINE;
		dseg++;
	}

	/* write the dma part */
	dseg->addr       = cpu_to_be64(dma_addr);
	dseg->byte_count = cpu_to_be32(dma_len);

	cseg->opmod_idx_opcode = cpu_to_be32((sq->pc << 8) | MLX5_OPCODE_SEND);

	/* move page to reference to sq responsibility,
	 * and mark so it's not put back in page-cache.
	 */
	sq->db.xdpi[pi] = *xdpi;
	sq->pc++;

	sq->doorbell = true;

	stats->xmit++;
	return true;
}