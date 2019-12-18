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
struct mdp5_encoder {int /*<<< orphan*/  ctl; TYPE_1__* intf; } ;
struct drm_encoder {int dummy; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device dev; } ;
struct TYPE_3__ {int num; } ;

/* Variables and functions */
 int EINVAL ; 
 int MDP5_SPLIT_DPL_LOWER_INTF1_TG_SYNC ; 
 int MDP5_SPLIT_DPL_LOWER_INTF2_TG_SYNC ; 
 int /*<<< orphan*/  REG_MDP5_SPLIT_DPL_EN ; 
 int /*<<< orphan*/  REG_MDP5_SPLIT_DPL_LOWER ; 
 int /*<<< orphan*/  REG_MDP5_SPLIT_DPL_UPPER ; 
 struct mdp5_kms* get_kms (struct drm_encoder*) ; 
 int /*<<< orphan*/  mdp5_ctl_pair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mdp5_write (struct mdp5_kms*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm_runtime_get_sync (struct device*) ; 
 int /*<<< orphan*/  pm_runtime_put_sync (struct device*) ; 
 struct mdp5_encoder* to_mdp5_encoder (struct drm_encoder*) ; 

int mdp5_vid_encoder_set_split_display(struct drm_encoder *encoder,
				       struct drm_encoder *slave_encoder)
{
	struct mdp5_encoder *mdp5_encoder = to_mdp5_encoder(encoder);
	struct mdp5_encoder *mdp5_slave_enc = to_mdp5_encoder(slave_encoder);
	struct mdp5_kms *mdp5_kms;
	struct device *dev;
	int intf_num;
	u32 data = 0;

	if (!encoder || !slave_encoder)
		return -EINVAL;

	mdp5_kms = get_kms(encoder);
	intf_num = mdp5_encoder->intf->num;

	/* Switch slave encoder's TimingGen Sync mode,
	 * to use the master's enable signal for the slave encoder.
	 */
	if (intf_num == 1)
		data |= MDP5_SPLIT_DPL_LOWER_INTF2_TG_SYNC;
	else if (intf_num == 2)
		data |= MDP5_SPLIT_DPL_LOWER_INTF1_TG_SYNC;
	else
		return -EINVAL;

	dev = &mdp5_kms->pdev->dev;
	/* Make sure clocks are on when connectors calling this function. */
	pm_runtime_get_sync(dev);

	/* Dumb Panel, Sync mode */
	mdp5_write(mdp5_kms, REG_MDP5_SPLIT_DPL_UPPER, 0);
	mdp5_write(mdp5_kms, REG_MDP5_SPLIT_DPL_LOWER, data);
	mdp5_write(mdp5_kms, REG_MDP5_SPLIT_DPL_EN, 1);

	mdp5_ctl_pair(mdp5_encoder->ctl, mdp5_slave_enc->ctl, true);

	pm_runtime_put_sync(dev);

	return 0;
}