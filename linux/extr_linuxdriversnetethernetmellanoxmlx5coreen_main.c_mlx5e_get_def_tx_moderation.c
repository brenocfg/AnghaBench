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
typedef  scalar_t__ u8 ;
struct net_dim_cq_moder {int /*<<< orphan*/  usec; int /*<<< orphan*/  pkts; scalar_t__ cq_period_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  MLX5E_PARAMS_DEFAULT_TX_CQ_MODERATION_PKTS ; 
 int /*<<< orphan*/  MLX5E_PARAMS_DEFAULT_TX_CQ_MODERATION_USEC ; 
 int /*<<< orphan*/  MLX5E_PARAMS_DEFAULT_TX_CQ_MODERATION_USEC_FROM_CQE ; 
 scalar_t__ MLX5_CQ_PERIOD_MODE_START_FROM_CQE ; 

__attribute__((used)) static struct net_dim_cq_moder mlx5e_get_def_tx_moderation(u8 cq_period_mode)
{
	struct net_dim_cq_moder moder;

	moder.cq_period_mode = cq_period_mode;
	moder.pkts = MLX5E_PARAMS_DEFAULT_TX_CQ_MODERATION_PKTS;
	moder.usec = MLX5E_PARAMS_DEFAULT_TX_CQ_MODERATION_USEC;
	if (cq_period_mode == MLX5_CQ_PERIOD_MODE_START_FROM_CQE)
		moder.usec = MLX5E_PARAMS_DEFAULT_TX_CQ_MODERATION_USEC_FROM_CQE;

	return moder;
}