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
struct TYPE_4__ {scalar_t__ in_cs; } ;
struct TYPE_3__ {scalar_t__ in_cs; } ;
struct ipu_flow {int out_cs; TYPE_2__ foreground; TYPE_1__ background; struct ipu_dp_priv* priv; } ;
struct ipu_dp_priv {int /*<<< orphan*/  mutex; int /*<<< orphan*/  ipu; } ;
struct ipu_dp {int in_cs; int /*<<< orphan*/  foreground; } ;
typedef  enum ipu_color_space { ____Placeholder_ipu_color_space } ipu_color_space ;

/* Variables and functions */
 int /*<<< orphan*/  DP_COM_CONF_CSC_DEF_BG ; 
 int /*<<< orphan*/  DP_COM_CONF_CSC_DEF_BOTH ; 
 int /*<<< orphan*/  DP_COM_CONF_CSC_DEF_FG ; 
 scalar_t__ IPUV3_COLORSPACE_UNKNOWN ; 
 int /*<<< orphan*/  ipu_dp_csc_init (struct ipu_flow*,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipu_srm_dp_update (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct ipu_flow* to_flow (struct ipu_dp*) ; 

int ipu_dp_setup_channel(struct ipu_dp *dp,
		enum ipu_color_space in,
		enum ipu_color_space out)
{
	struct ipu_flow *flow = to_flow(dp);
	struct ipu_dp_priv *priv = flow->priv;

	mutex_lock(&priv->mutex);

	dp->in_cs = in;

	if (!dp->foreground)
		flow->out_cs = out;

	if (flow->foreground.in_cs == flow->background.in_cs) {
		/*
		 * foreground and background are of same colorspace, put
		 * colorspace converter after combining unit.
		 */
		ipu_dp_csc_init(flow, flow->foreground.in_cs, flow->out_cs,
				DP_COM_CONF_CSC_DEF_BOTH);
	} else {
		if (flow->foreground.in_cs == IPUV3_COLORSPACE_UNKNOWN ||
		    flow->foreground.in_cs == flow->out_cs)
			/*
			 * foreground identical to output, apply color
			 * conversion on background
			 */
			ipu_dp_csc_init(flow, flow->background.in_cs,
					flow->out_cs, DP_COM_CONF_CSC_DEF_BG);
		else
			ipu_dp_csc_init(flow, flow->foreground.in_cs,
					flow->out_cs, DP_COM_CONF_CSC_DEF_FG);
	}

	ipu_srm_dp_update(priv->ipu, true);

	mutex_unlock(&priv->mutex);

	return 0;
}