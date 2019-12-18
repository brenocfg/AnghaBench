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
struct wl1271 {scalar_t__ plt_mode; } ;
struct nlattr {int dummy; } ;
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct wl1271* priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 scalar_t__ PLT_CHIP_AWAKE ; 
 size_t WL1271_TM_ATTR_CMD_ID ; 
 int /*<<< orphan*/  WL1271_TM_ATTR_MAX ; 
#define  WL1271_TM_CMD_CONFIGURE 132 
#define  WL1271_TM_CMD_GET_MAC 131 
#define  WL1271_TM_CMD_INTERROGATE 130 
#define  WL1271_TM_CMD_SET_PLT_MODE 129 
#define  WL1271_TM_CMD_TEST 128 
 int nla_get_u32 (struct nlattr*) ; 
 int nla_parse_deprecated (struct nlattr**,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int wl1271_tm_cmd_configure (struct wl1271*,struct nlattr**) ; 
 int wl1271_tm_cmd_interrogate (struct wl1271*,struct nlattr**) ; 
 int wl1271_tm_cmd_set_plt_mode (struct wl1271*,struct nlattr**) ; 
 int wl1271_tm_cmd_test (struct wl1271*,struct nlattr**) ; 
 int /*<<< orphan*/  wl1271_tm_policy ; 
 int wl12xx_tm_cmd_get_mac (struct wl1271*,struct nlattr**) ; 

int wl1271_tm_cmd(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
		  void *data, int len)
{
	struct wl1271 *wl = hw->priv;
	struct nlattr *tb[WL1271_TM_ATTR_MAX + 1];
	u32 nla_cmd;
	int err;

	err = nla_parse_deprecated(tb, WL1271_TM_ATTR_MAX, data, len,
				   wl1271_tm_policy, NULL);
	if (err)
		return err;

	if (!tb[WL1271_TM_ATTR_CMD_ID])
		return -EINVAL;

	nla_cmd = nla_get_u32(tb[WL1271_TM_ATTR_CMD_ID]);

	/* Only SET_PLT_MODE is allowed in case of mode PLT_CHIP_AWAKE */
	if (wl->plt_mode == PLT_CHIP_AWAKE &&
	    nla_cmd != WL1271_TM_CMD_SET_PLT_MODE)
		return -EOPNOTSUPP;

	switch (nla_cmd) {
	case WL1271_TM_CMD_TEST:
		return wl1271_tm_cmd_test(wl, tb);
	case WL1271_TM_CMD_INTERROGATE:
		return wl1271_tm_cmd_interrogate(wl, tb);
	case WL1271_TM_CMD_CONFIGURE:
		return wl1271_tm_cmd_configure(wl, tb);
	case WL1271_TM_CMD_SET_PLT_MODE:
		return wl1271_tm_cmd_set_plt_mode(wl, tb);
	case WL1271_TM_CMD_GET_MAC:
		return wl12xx_tm_cmd_get_mac(wl, tb);
	default:
		return -EOPNOTSUPP;
	}
}