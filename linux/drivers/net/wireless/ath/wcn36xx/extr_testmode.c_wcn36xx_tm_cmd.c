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
struct wcn36xx {int dummy; } ;
struct nlattr {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct wcn36xx* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  WCN36XX_DBG_TESTMODE_DUMP ; 
 size_t WCN36XX_TM_ATTR_CMD ; 
 int /*<<< orphan*/  WCN36XX_TM_ATTR_MAX ; 
 unsigned short WCN36XX_TM_CMD_PTT ; 
 unsigned short nla_get_u16 (struct nlattr*) ; 
 int nla_parse_deprecated (struct nlattr**,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wcn36xx_dbg_dump (int /*<<< orphan*/ ,char*,void*,int) ; 
 int wcn36xx_tm_cmd_ptt (struct wcn36xx*,struct ieee80211_vif*,struct nlattr**) ; 
 int /*<<< orphan*/  wcn36xx_tm_policy ; 

int wcn36xx_tm_cmd(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		   void *data, int len)
{
	struct wcn36xx *wcn = hw->priv;
	struct nlattr *tb[WCN36XX_TM_ATTR_MAX + 1];
	int ret = 0;
	unsigned short attr;

	wcn36xx_dbg_dump(WCN36XX_DBG_TESTMODE_DUMP, "Data:", data, len);
	ret = nla_parse_deprecated(tb, WCN36XX_TM_ATTR_MAX, data, len,
				   wcn36xx_tm_policy, NULL);
	if (ret)
		return ret;

	if (!tb[WCN36XX_TM_ATTR_CMD])
		return -EINVAL;

	attr = nla_get_u16(tb[WCN36XX_TM_ATTR_CMD]);

	if (attr != WCN36XX_TM_CMD_PTT)
		return -EOPNOTSUPP;

	return wcn36xx_tm_cmd_ptt(wcn, vif, tb);
}