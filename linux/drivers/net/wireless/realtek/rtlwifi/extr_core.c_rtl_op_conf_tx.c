#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u16 ;
struct rtl_priv {TYPE_3__* cfg; } ;
struct rtl_mac {int /*<<< orphan*/ * edca_param; TYPE_1__* ac; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_tx_queue_params {int /*<<< orphan*/  txop; int /*<<< orphan*/  cw_max; int /*<<< orphan*/  cw_min; int /*<<< orphan*/  aifs; } ;
struct ieee80211_hw {int dummy; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* set_qos ) (struct ieee80211_hw*,int) ;} ;
struct TYPE_4__ {void* tx_op; void* cw_max; void* cw_min; int /*<<< orphan*/  aifs; } ;

/* Variables and functions */
 scalar_t__ AC_MAX ; 
 int /*<<< orphan*/  COMP_ERR ; 
 int /*<<< orphan*/  DBG_WARNING ; 
 int EINVAL ; 
 int /*<<< orphan*/  RT_TRACE (struct rtl_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int _rtl_get_hal_qnum (scalar_t__) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct ieee80211_tx_queue_params const*,int) ; 
 struct rtl_mac* rtl_mac (struct rtl_priv*) ; 
 struct rtl_priv* rtl_priv (struct ieee80211_hw*) ; 
 int /*<<< orphan*/  stub1 (struct ieee80211_hw*,int) ; 

__attribute__((used)) static int rtl_op_conf_tx(struct ieee80211_hw *hw,
			  struct ieee80211_vif *vif, u16 queue,
			  const struct ieee80211_tx_queue_params *param)
{
	struct rtl_priv *rtlpriv = rtl_priv(hw);
	struct rtl_mac *mac = rtl_mac(rtl_priv(hw));
	int aci;

	if (queue >= AC_MAX) {
		RT_TRACE(rtlpriv, COMP_ERR, DBG_WARNING,
			 "queue number %d is incorrect!\n", queue);
		return -EINVAL;
	}

	aci = _rtl_get_hal_qnum(queue);
	mac->ac[aci].aifs = param->aifs;
	mac->ac[aci].cw_min = cpu_to_le16(param->cw_min);
	mac->ac[aci].cw_max = cpu_to_le16(param->cw_max);
	mac->ac[aci].tx_op = cpu_to_le16(param->txop);
	memcpy(&mac->edca_param[aci], param, sizeof(*param));
	rtlpriv->cfg->ops->set_qos(hw, aci);
	return 0;
}