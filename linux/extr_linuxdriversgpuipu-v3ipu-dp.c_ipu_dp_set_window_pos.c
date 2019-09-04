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
typedef  int u16 ;
struct ipu_flow {scalar_t__ base; struct ipu_dp_priv* priv; } ;
struct ipu_dp_priv {int /*<<< orphan*/  ipu; } ;
struct ipu_dp {int dummy; } ;

/* Variables and functions */
 scalar_t__ DP_FG_POS ; 
 int /*<<< orphan*/  ipu_srm_dp_update (int /*<<< orphan*/ ,int) ; 
 struct ipu_flow* to_flow (struct ipu_dp*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int ipu_dp_set_window_pos(struct ipu_dp *dp, u16 x_pos, u16 y_pos)
{
	struct ipu_flow *flow = to_flow(dp);
	struct ipu_dp_priv *priv = flow->priv;

	writel((x_pos << 16) | y_pos, flow->base + DP_FG_POS);

	ipu_srm_dp_update(priv->ipu, true);

	return 0;
}