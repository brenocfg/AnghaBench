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
struct ipu_flow {scalar_t__ base; struct ipu_dp_priv* priv; } ;
struct ipu_dp_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  ipu; } ;
struct ipu_dp {int /*<<< orphan*/  foreground; } ;

/* Variables and functions */
 scalar_t__ DP_COM_CONF ; 
 int /*<<< orphan*/  DP_COM_CONF_FG_EN ; 
 int /*<<< orphan*/  ipu_srm_dp_update (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 struct ipu_flow* to_flow (struct ipu_dp*) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

int ipu_dp_enable_channel(struct ipu_dp *dp)
{
	struct ipu_flow *flow = to_flow(dp);
	struct ipu_dp_priv *priv = flow->priv;
	u32 reg;

	if (!dp->foreground)
		return 0;

	mutex_lock(&priv->mutex);

	reg = readl(flow->base + DP_COM_CONF);
	reg |= DP_COM_CONF_FG_EN;
	writel(reg, flow->base + DP_COM_CONF);

	ipu_srm_dp_update(priv->ipu, true);

	mutex_unlock(&priv->mutex);

	return 0;
}