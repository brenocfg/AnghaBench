#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_7__ {int /*<<< orphan*/  asq_last_status; } ;
struct TYPE_10__ {TYPE_1__ aq; } ;
struct i40e_pf {TYPE_3__* pdev; TYPE_4__ hw; } ;
struct i40e_aqc_switch_config_element_resp {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  num_total; int /*<<< orphan*/  num_reported; } ;
struct i40e_aqc_get_switch_config_resp {struct i40e_aqc_switch_config_element_resp* element; TYPE_2__ header; } ;
struct TYPE_9__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOENT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  I40E_AQ_LARGE_BUF ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__) ; 
 int i40e_aq_get_switch_config (TYPE_4__*,struct i40e_aqc_get_switch_config_resp*,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ i40e_aq_str (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_setup_pf_switch_element (struct i40e_pf*,struct i40e_aqc_switch_config_element_resp*,scalar_t__,int) ; 
 scalar_t__ i40e_stat_str (TYPE_4__*,int) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kzalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 

int i40e_fetch_switch_configuration(struct i40e_pf *pf, bool printconfig)
{
	struct i40e_aqc_get_switch_config_resp *sw_config;
	u16 next_seid = 0;
	int ret = 0;
	u8 *aq_buf;
	int i;

	aq_buf = kzalloc(I40E_AQ_LARGE_BUF, GFP_KERNEL);
	if (!aq_buf)
		return -ENOMEM;

	sw_config = (struct i40e_aqc_get_switch_config_resp *)aq_buf;
	do {
		u16 num_reported, num_total;

		ret = i40e_aq_get_switch_config(&pf->hw, sw_config,
						I40E_AQ_LARGE_BUF,
						&next_seid, NULL);
		if (ret) {
			dev_info(&pf->pdev->dev,
				 "get switch config failed err %s aq_err %s\n",
				 i40e_stat_str(&pf->hw, ret),
				 i40e_aq_str(&pf->hw,
					     pf->hw.aq.asq_last_status));
			kfree(aq_buf);
			return -ENOENT;
		}

		num_reported = le16_to_cpu(sw_config->header.num_reported);
		num_total = le16_to_cpu(sw_config->header.num_total);

		if (printconfig)
			dev_info(&pf->pdev->dev,
				 "header: %d reported %d total\n",
				 num_reported, num_total);

		for (i = 0; i < num_reported; i++) {
			struct i40e_aqc_switch_config_element_resp *ele =
				&sw_config->element[i];

			i40e_setup_pf_switch_element(pf, ele, num_reported,
						     printconfig);
		}
	} while (next_seid != 0);

	kfree(aq_buf);
	return ret;
}