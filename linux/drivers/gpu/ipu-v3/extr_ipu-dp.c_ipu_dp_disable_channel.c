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
struct ipu_flow {scalar_t__ base; struct ipu_dp_priv* priv; } ;
struct ipu_dp_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  ipu; } ;
struct ipu_dp {int /*<<< orphan*/  foreground; int /*<<< orphan*/  in_cs; } ;

/* Variables and functions */
 scalar_t__ DP_COM_CONF ; 
 int DP_COM_CONF_CSC_DEF_BG ; 
 int DP_COM_CONF_CSC_DEF_BOTH ; 
 int DP_COM_CONF_CSC_DEF_MASK ; 
 int DP_COM_CONF_FG_EN ; 
 scalar_t__ DP_FG_POS ; 
 int /*<<< orphan*/  IPUV3_COLORSPACE_UNKNOWN ; 
 int /*<<< orphan*/  ipu_srm_dp_update (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 struct ipu_flow* to_flow (struct ipu_dp*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

void ipu_dp_disable_channel(struct ipu_dp *dp, bool sync)
{
	struct ipu_flow *flow = to_flow(dp);
	struct ipu_dp_priv *priv = flow->priv;
	u32 reg, csc;

	dp->in_cs = IPUV3_COLORSPACE_UNKNOWN;

	if (!dp->foreground)
		return;

	mutex_lock(&priv->mutex);

	reg = readl(flow->base + DP_COM_CONF);
	csc = reg & DP_COM_CONF_CSC_DEF_MASK;
	reg &= ~DP_COM_CONF_CSC_DEF_MASK;
	if (csc == DP_COM_CONF_CSC_DEF_BOTH || csc == DP_COM_CONF_CSC_DEF_BG)
		reg |= DP_COM_CONF_CSC_DEF_BG;

	reg &= ~DP_COM_CONF_FG_EN;
	writel(reg, flow->base + DP_COM_CONF);

	writel(0, flow->base + DP_FG_POS);
	ipu_srm_dp_update(priv->ipu, sync);

	mutex_unlock(&priv->mutex);
}