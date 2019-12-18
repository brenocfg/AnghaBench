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
struct wcn36xx_vif {int /*<<< orphan*/  self_dpu_desc_index; int /*<<< orphan*/  self_sta_index; } ;
struct wcn36xx_hal_add_sta_self_rsp_msg {scalar_t__ status; int /*<<< orphan*/  dpu_index; int /*<<< orphan*/  self_sta_index; } ;
struct wcn36xx {int dummy; } ;
struct ieee80211_vif {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  WCN36XX_DBG_HAL ; 
 scalar_t__ WCN36XX_FW_MSG_RESULT_SUCCESS ; 
 int /*<<< orphan*/  wcn36xx_dbg (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct wcn36xx_vif* wcn36xx_vif_to_priv (struct ieee80211_vif*) ; 
 int /*<<< orphan*/  wcn36xx_warn (char*,scalar_t__) ; 

__attribute__((used)) static int wcn36xx_smd_add_sta_self_rsp(struct wcn36xx *wcn,
					struct ieee80211_vif *vif,
					void *buf,
					size_t len)
{
	struct wcn36xx_hal_add_sta_self_rsp_msg *rsp;
	struct wcn36xx_vif *vif_priv = wcn36xx_vif_to_priv(vif);

	if (len < sizeof(*rsp))
		return -EINVAL;

	rsp = (struct wcn36xx_hal_add_sta_self_rsp_msg *)buf;

	if (rsp->status != WCN36XX_FW_MSG_RESULT_SUCCESS) {
		wcn36xx_warn("hal add sta self failure: %d\n",
			     rsp->status);
		return rsp->status;
	}

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal add sta self status %d self_sta_index %d dpu_index %d\n",
		    rsp->status, rsp->self_sta_index, rsp->dpu_index);

	vif_priv->self_sta_index = rsp->self_sta_index;
	vif_priv->self_dpu_desc_index = rsp->dpu_index;

	return 0;
}