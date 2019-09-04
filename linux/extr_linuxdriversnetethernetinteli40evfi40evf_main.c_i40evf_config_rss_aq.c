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
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_6__ {int /*<<< orphan*/  asq_last_status; } ;
struct i40e_hw {TYPE_3__ aq; } ;
struct i40evf_adapter {scalar_t__ current_op; TYPE_2__* pdev; int /*<<< orphan*/  rss_lut_size; int /*<<< orphan*/  rss_lut; TYPE_1__ vsi; struct i40e_hw hw; scalar_t__ rss_key; } ;
struct i40e_aqc_get_set_rss_key_data {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ VIRTCHNL_OP_UNKNOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__,...) ; 
 int i40evf_aq_set_rss_key (struct i40e_hw*,int /*<<< orphan*/ ,struct i40e_aqc_get_set_rss_key_data*) ; 
 int i40evf_aq_set_rss_lut (struct i40e_hw*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40evf_aq_str (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40evf_stat_str (struct i40e_hw*,int) ; 

__attribute__((used)) static int i40evf_config_rss_aq(struct i40evf_adapter *adapter)
{
	struct i40e_aqc_get_set_rss_key_data *rss_key =
		(struct i40e_aqc_get_set_rss_key_data *)adapter->rss_key;
	struct i40e_hw *hw = &adapter->hw;
	int ret = 0;

	if (adapter->current_op != VIRTCHNL_OP_UNKNOWN) {
		/* bail because we already have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot configure RSS, command %d pending\n",
			adapter->current_op);
		return -EBUSY;
	}

	ret = i40evf_aq_set_rss_key(hw, adapter->vsi.id, rss_key);
	if (ret) {
		dev_err(&adapter->pdev->dev, "Cannot set RSS key, err %s aq_err %s\n",
			i40evf_stat_str(hw, ret),
			i40evf_aq_str(hw, hw->aq.asq_last_status));
		return ret;

	}

	ret = i40evf_aq_set_rss_lut(hw, adapter->vsi.id, false,
				    adapter->rss_lut, adapter->rss_lut_size);
	if (ret) {
		dev_err(&adapter->pdev->dev, "Cannot set RSS lut, err %s aq_err %s\n",
			i40evf_stat_str(hw, ret),
			i40evf_aq_str(hw, hw->aq.asq_last_status));
	}

	return ret;

}