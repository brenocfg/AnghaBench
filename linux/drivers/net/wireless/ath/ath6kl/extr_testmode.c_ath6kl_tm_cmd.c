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
struct wireless_dev {int dummy; } ;
struct wiphy {int dummy; } ;
struct nlattr {int dummy; } ;
struct ath6kl {int /*<<< orphan*/  wmi; } ;

/* Variables and functions */
 size_t ATH6KL_TM_ATTR_CMD ; 
 size_t ATH6KL_TM_ATTR_DATA ; 
 int /*<<< orphan*/  ATH6KL_TM_ATTR_MAX ; 
#define  ATH6KL_TM_CMD_RX_REPORT 129 
#define  ATH6KL_TM_CMD_TCMD 128 
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ath6kl_tm_policy ; 
 int /*<<< orphan*/  ath6kl_wmi_test_cmd (int /*<<< orphan*/ ,void*,int) ; 
 void* nla_data (struct nlattr*) ; 
 int nla_get_u32 (struct nlattr*) ; 
 int nla_len (struct nlattr*) ; 
 int nla_parse_deprecated (struct nlattr**,int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ath6kl* wiphy_priv (struct wiphy*) ; 

int ath6kl_tm_cmd(struct wiphy *wiphy, struct wireless_dev *wdev,
		  void *data, int len)
{
	struct ath6kl *ar = wiphy_priv(wiphy);
	struct nlattr *tb[ATH6KL_TM_ATTR_MAX + 1];
	int err, buf_len;
	void *buf;

	err = nla_parse_deprecated(tb, ATH6KL_TM_ATTR_MAX, data, len,
				   ath6kl_tm_policy, NULL);
	if (err)
		return err;

	if (!tb[ATH6KL_TM_ATTR_CMD])
		return -EINVAL;

	switch (nla_get_u32(tb[ATH6KL_TM_ATTR_CMD])) {
	case ATH6KL_TM_CMD_TCMD:
		if (!tb[ATH6KL_TM_ATTR_DATA])
			return -EINVAL;

		buf = nla_data(tb[ATH6KL_TM_ATTR_DATA]);
		buf_len = nla_len(tb[ATH6KL_TM_ATTR_DATA]);

		ath6kl_wmi_test_cmd(ar->wmi, buf, buf_len);

		return 0;

		break;
	case ATH6KL_TM_CMD_RX_REPORT:
	default:
		return -EOPNOTSUPP;
	}
}