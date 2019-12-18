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
typedef  int /*<<< orphan*/  u32 ;
struct mlx5e_txqsq {int dummy; } ;
struct mlx5e_tx_wqe_info {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void
mlx5e_ktls_tx_handle_resync_dump_comp(struct mlx5e_txqsq *sq,
				      struct mlx5e_tx_wqe_info *wi,
				      u32 *dma_fifo_cc) {}