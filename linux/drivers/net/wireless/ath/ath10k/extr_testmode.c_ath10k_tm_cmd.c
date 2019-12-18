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
struct nlattr {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct ath10k* priv; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 size_t ATH10K_TM_ATTR_CMD ; 
 int /*<<< orphan*/  ATH10K_TM_ATTR_MAX ; 
#define  ATH10K_TM_CMD_GET_VERSION 131 
#define  ATH10K_TM_CMD_UTF_START 130 
#define  ATH10K_TM_CMD_UTF_STOP 129 
#define  ATH10K_TM_CMD_WMI 128 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int ath10k_tm_cmd_get_version (struct ath10k*,struct nlattr**) ; 
 int ath10k_tm_cmd_utf_start (struct ath10k*,struct nlattr**) ; 
 int ath10k_tm_cmd_utf_stop (struct ath10k*,struct nlattr**) ; 
 int ath10k_tm_cmd_wmi (struct ath10k*,struct nlattr**) ; 
 int /*<<< orphan*/  ath10k_tm_policy ; 
 int nla_get_u32 (struct nlattr*) ; 
 int nla_parse_deprecated (struct nlattr**,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int ath10k_tm_cmd(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		  void *data, int len)
{
	struct ath10k *ar = hw->priv;
	struct nlattr *tb[ATH10K_TM_ATTR_MAX + 1];
	int ret;

	ret = nla_parse_deprecated(tb, ATH10K_TM_ATTR_MAX, data, len,
				   ath10k_tm_policy, NULL);
	if (ret)
		return ret;

	if (!tb[ATH10K_TM_ATTR_CMD])
		return -EINVAL;

	switch (nla_get_u32(tb[ATH10K_TM_ATTR_CMD])) {
	case ATH10K_TM_CMD_GET_VERSION:
		return ath10k_tm_cmd_get_version(ar, tb);
	case ATH10K_TM_CMD_UTF_START:
		return ath10k_tm_cmd_utf_start(ar, tb);
	case ATH10K_TM_CMD_UTF_STOP:
		return ath10k_tm_cmd_utf_stop(ar, tb);
	case ATH10K_TM_CMD_WMI:
		return ath10k_tm_cmd_wmi(ar, tb);
	default:
		return -EOPNOTSUPP;
	}
}