#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_9__ {int asq_last_status; } ;
struct TYPE_11__ {int partition_id; TYPE_1__ aq; } ;
struct i40e_pf {TYPE_3__ hw; TYPE_2__* pdev; } ;
typedef  int /*<<< orphan*/  nvm_word ;
typedef  scalar_t__ i40e_status ;
typedef  enum i40e_admin_queue_err { ____Placeholder_i40e_admin_queue_err } i40e_admin_queue_err ;
struct TYPE_10__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ I40E_NOT_SUPPORTED ; 
 int /*<<< orphan*/  I40E_RESOURCE_READ ; 
 int /*<<< orphan*/  I40E_RESOURCE_WRITE ; 
 int /*<<< orphan*/  I40E_SR_NVM_CONTROL_WORD ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,...) ; 
 scalar_t__ i40e_acquire_nvm (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_aq_read_nvm (TYPE_3__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_aq_str (TYPE_3__*,int) ; 
 scalar_t__ i40e_aq_update_nvm (TYPE_3__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_release_nvm (TYPE_3__*) ; 
 int /*<<< orphan*/  i40e_stat_str (TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  msleep (int) ; 

i40e_status i40e_commit_partition_bw_setting(struct i40e_pf *pf)
{
	/* Commit temporary BW setting to permanent NVM image */
	enum i40e_admin_queue_err last_aq_status;
	i40e_status ret;
	u16 nvm_word;

	if (pf->hw.partition_id != 1) {
		dev_info(&pf->pdev->dev,
			 "Commit BW only works on partition 1! This is partition %d",
			 pf->hw.partition_id);
		ret = I40E_NOT_SUPPORTED;
		goto bw_commit_out;
	}

	/* Acquire NVM for read access */
	ret = i40e_acquire_nvm(&pf->hw, I40E_RESOURCE_READ);
	last_aq_status = pf->hw.aq.asq_last_status;
	if (ret) {
		dev_info(&pf->pdev->dev,
			 "Cannot acquire NVM for read access, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, last_aq_status));
		goto bw_commit_out;
	}

	/* Read word 0x10 of NVM - SW compatibility word 1 */
	ret = i40e_aq_read_nvm(&pf->hw,
			       I40E_SR_NVM_CONTROL_WORD,
			       0x10, sizeof(nvm_word), &nvm_word,
			       false, NULL);
	/* Save off last admin queue command status before releasing
	 * the NVM
	 */
	last_aq_status = pf->hw.aq.asq_last_status;
	i40e_release_nvm(&pf->hw);
	if (ret) {
		dev_info(&pf->pdev->dev, "NVM read error, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, last_aq_status));
		goto bw_commit_out;
	}

	/* Wait a bit for NVM release to complete */
	msleep(50);

	/* Acquire NVM for write access */
	ret = i40e_acquire_nvm(&pf->hw, I40E_RESOURCE_WRITE);
	last_aq_status = pf->hw.aq.asq_last_status;
	if (ret) {
		dev_info(&pf->pdev->dev,
			 "Cannot acquire NVM for write access, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, last_aq_status));
		goto bw_commit_out;
	}
	/* Write it back out unchanged to initiate update NVM,
	 * which will force a write of the shadow (alt) RAM to
	 * the NVM - thus storing the bandwidth values permanently.
	 */
	ret = i40e_aq_update_nvm(&pf->hw,
				 I40E_SR_NVM_CONTROL_WORD,
				 0x10, sizeof(nvm_word),
				 &nvm_word, true, 0, NULL);
	/* Save off last admin queue command status before releasing
	 * the NVM
	 */
	last_aq_status = pf->hw.aq.asq_last_status;
	i40e_release_nvm(&pf->hw);
	if (ret)
		dev_info(&pf->pdev->dev,
			 "BW settings NOT SAVED, err %s aq_err %s\n",
			 i40e_stat_str(&pf->hw, ret),
			 i40e_aq_str(&pf->hw, last_aq_status));
bw_commit_out:

	return ret;
}