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
typedef  int u32 ;
typedef  int u16 ;
struct mlx5e_xdpsq_stats {int /*<<< orphan*/  inlnw; } ;
struct mlx5e_xdp_mpwqe {int ds_count; scalar_t__ inline_on; int /*<<< orphan*/  pkt_count; scalar_t__ wqe; } ;
struct mlx5e_xdpsq {int /*<<< orphan*/  mkey_be; struct mlx5e_xdp_mpwqe mpwqe; } ;
struct mlx5e_xdp_xmit_data {int len; int /*<<< orphan*/  dma_addr; int /*<<< orphan*/  data; } ;
struct mlx5_wqe_inline_seg {int /*<<< orphan*/  data; void* byte_count; } ;
struct mlx5_wqe_data_seg {int /*<<< orphan*/  lkey; void* byte_count; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int DIV_ROUND_UP (int,int /*<<< orphan*/ ) ; 
 int MLX5E_XDP_INLINE_WQE_SZ_THRSD ; 
 int MLX5_INLINE_SEG ; 
 int /*<<< orphan*/  MLX5_SEND_WQE_DS ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static inline void
mlx5e_xdp_mpwqe_add_dseg(struct mlx5e_xdpsq *sq,
			 struct mlx5e_xdp_xmit_data *xdptxd,
			 struct mlx5e_xdpsq_stats *stats)
{
	struct mlx5e_xdp_mpwqe *session = &sq->mpwqe;
	struct mlx5_wqe_data_seg *dseg =
		(struct mlx5_wqe_data_seg *)session->wqe + session->ds_count;
	u32 dma_len = xdptxd->len;

	session->pkt_count++;

	if (session->inline_on && dma_len <= MLX5E_XDP_INLINE_WQE_SZ_THRSD) {
		struct mlx5_wqe_inline_seg *inline_dseg =
			(struct mlx5_wqe_inline_seg *)dseg;
		u16 ds_len = sizeof(*inline_dseg) + dma_len;
		u16 ds_cnt = DIV_ROUND_UP(ds_len, MLX5_SEND_WQE_DS);

		inline_dseg->byte_count = cpu_to_be32(dma_len | MLX5_INLINE_SEG);
		memcpy(inline_dseg->data, xdptxd->data, dma_len);

		session->ds_count += ds_cnt;
		stats->inlnw++;
		return;
	}

	dseg->addr       = cpu_to_be64(xdptxd->dma_addr);
	dseg->byte_count = cpu_to_be32(dma_len);
	dseg->lkey       = sq->mkey_be;
	session->ds_count++;
}