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
typedef  int u32 ;
struct mdp5_kms {TYPE_2__* pdev; } ;
struct mdp5_encoder {TYPE_1__* intf; } ;
struct drm_encoder {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;
struct TYPE_3__ {int num; } ;

/* Variables and functions */
 int EINVAL ; 
 int MDP5_SPLIT_DPL_LOWER_SMART_PANEL ; 
 int MDP5_SPLIT_DPL_UPPER_INTF1_SW_TRG_MUX ; 
 int MDP5_SPLIT_DPL_UPPER_INTF2_SW_TRG_MUX ; 
 int MDP5_SPLIT_DPL_UPPER_SMART_PANEL ; 
 int /*<<< orphan*/  REG_MDP5_SPLIT_DPL_EN ; 
 int /*<<< orphan*/  REG_MDP5_SPLIT_DPL_LOWER ; 
 int /*<<< orphan*/  REG_MDP5_SPLIT_DPL_UPPER ; 
 struct mdp5_kms* get_kms (struct drm_encoder*) ; 
 int /*<<< orphan*/  mdp5_write (struct mdp5_kms*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 struct mdp5_encoder* to_mdp5_encoder (struct drm_encoder*) ; 

int mdp5_cmd_encoder_set_split_display(struct drm_encoder *encoder,
				       struct drm_encoder *slave_encoder)
{
	struct mdp5_encoder *mdp5_cmd_enc = to_mdp5_encoder(encoder);
	struct mdp5_kms *mdp5_kms;
	struct device *dev;
	int intf_num;
	u32 data = 0;

	if (!encoder || !slave_encoder)
		return -EINVAL;

	mdp5_kms = get_kms(encoder);
	intf_num = mdp5_cmd_enc->intf->num;

	/* Switch slave encoder's trigger MUX, to use the master's
	 * start signal for the slave encoder
	 */
	if (intf_num == 1)
		data |= MDP5_SPLIT_DPL_UPPER_INTF2_SW_TRG_MUX;
	else if (intf_num == 2)
		data |= MDP5_SPLIT_DPL_UPPER_INTF1_SW_TRG_MUX;
	else
		return -EINVAL;

	/* Smart Panel, Sync mode */
	data |= MDP5_SPLIT_DPL_UPPER_SMART_PANEL;

	dev = &mdp5_kms->pdev->dev;

	/* Make sure clocks are on when connectors calling this function. */
	pm_runtime_get_sync(dev);
	mdp5_write(mdp5_kms, REG_MDP5_SPLIT_DPL_UPPER, data);

	mdp5_write(mdp5_kms, REG_MDP5_SPLIT_DPL_LOWER,
		   MDP5_SPLIT_DPL_LOWER_SMART_PANEL);
	mdp5_write(mdp5_kms, REG_MDP5_SPLIT_DPL_EN, 1);
	pm_runtime_put_sync(dev);

	return 0;
}