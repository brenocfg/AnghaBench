#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ipu_soc {struct ipu_dp_priv* dp_priv; } ;
struct ipu_dp_priv {TYPE_1__* flow; } ;
struct ipu_dp {int in_use; } ;
struct TYPE_2__ {struct ipu_dp background; struct ipu_dp foreground; } ;

/* Variables and functions */
 int /*<<< orphan*/  EBUSY ; 
 int /*<<< orphan*/  EINVAL ; 
 struct ipu_dp* ERR_PTR (int /*<<< orphan*/ ) ; 
 unsigned int IPUV3_NUM_FLOWS ; 

struct ipu_dp *ipu_dp_get(struct ipu_soc *ipu, unsigned int flow)
{
	struct ipu_dp_priv *priv = ipu->dp_priv;
	struct ipu_dp *dp;

	if ((flow >> 1) >= IPUV3_NUM_FLOWS)
		return ERR_PTR(-EINVAL);

	if (flow & 1)
		dp = &priv->flow[flow >> 1].foreground;
	else
		dp = &priv->flow[flow >> 1].background;

	if (dp->in_use)
		return ERR_PTR(-EBUSY);

	dp->in_use = true;

	return dp;
}