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
typedef  int u32 ;
struct ipu_flow {scalar_t__ base; struct ipu_dp_priv* priv; } ;
struct ipu_dp_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  ipu; } ;
struct ipu_dp {int dummy; } ;

/* Variables and functions */
 scalar_t__ DP_COM_CONF ; 
 int DP_COM_CONF_GWAM ; 
 int DP_COM_CONF_GWSEL ; 
 scalar_t__ DP_GRAPH_WIND_CTRL ; 
 int /*<<< orphan*/  ipu_srm_dp_update (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int readl (scalar_t__) ; 
 struct ipu_flow* to_flow (struct ipu_dp*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

int ipu_dp_set_global_alpha(struct ipu_dp *dp, bool enable,
		u8 alpha, bool bg_chan)
{
	struct ipu_flow *flow = to_flow(dp);
	struct ipu_dp_priv *priv = flow->priv;
	u32 reg;

	mutex_lock(&priv->mutex);

	reg = readl(flow->base + DP_COM_CONF);
	if (bg_chan)
		reg &= ~DP_COM_CONF_GWSEL;
	else
		reg |= DP_COM_CONF_GWSEL;
	writel(reg, flow->base + DP_COM_CONF);

	if (enable) {
		reg = readl(flow->base + DP_GRAPH_WIND_CTRL) & 0x00FFFFFFL;
		writel(reg | ((u32) alpha << 24),
			     flow->base + DP_GRAPH_WIND_CTRL);

		reg = readl(flow->base + DP_COM_CONF);
		writel(reg | DP_COM_CONF_GWAM, flow->base + DP_COM_CONF);
	} else {
		reg = readl(flow->base + DP_COM_CONF);
		writel(reg & ~DP_COM_CONF_GWAM, flow->base + DP_COM_CONF);
	}

	ipu_srm_dp_update(priv->ipu, true);

	mutex_unlock(&priv->mutex);

	return 0;
}