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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_3__ {int /*<<< orphan*/  asq_last_status; } ;
struct i40e_hw {TYPE_1__ aq; } ;
struct i40e_pf {TYPE_2__* pdev; struct i40e_hw hw; } ;
struct i40e_info {struct i40e_pf* pf; } ;
struct i40e_client {int dummy; } ;
typedef  int i40e_status ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIRTCHNL_OP_IWARP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int i40e_aq_send_msg_to_vf (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int i40e_client_virtchnl_send(struct i40e_info *ldev,
				     struct i40e_client *client,
				     u32 vf_id, u8 *msg, u16 len)
{
	struct i40e_pf *pf = ldev->pf;
	struct i40e_hw *hw = &pf->hw;
	i40e_status err;

	err = i40e_aq_send_msg_to_vf(hw, vf_id, VIRTCHNL_OP_IWARP,
				     0, msg, len, NULL);
	if (err)
		dev_err(&pf->pdev->dev, "Unable to send iWarp message to VF, error %d, aq status %d\n",
			err, hw->aq.asq_last_status);

	return err;
}