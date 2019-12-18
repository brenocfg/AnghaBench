#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct mdp5_kms {int dummy; } ;
struct mdp5_ctl_manager {TYPE_1__* dev; int /*<<< orphan*/  single_flush_supported; } ;
struct mdp5_ctl {int status; struct mdp5_ctl* pair; struct mdp5_ctl_manager* ctlm; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CTL_STAT_BOOKED ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  MDP5_SPARE_0_SPLIT_DPL_SINGLE_FLUSH_EN ; 
 int /*<<< orphan*/  REG_MDP5_SPARE_0 ; 
 struct mdp5_kms* get_kms (struct mdp5_ctl_manager*) ; 
 int /*<<< orphan*/  mdp5_write (struct mdp5_kms*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int mdp5_ctl_pair(struct mdp5_ctl *ctlx, struct mdp5_ctl *ctly, bool enable)
{
	struct mdp5_ctl_manager *ctl_mgr = ctlx->ctlm;
	struct mdp5_kms *mdp5_kms = get_kms(ctl_mgr);

	/* do nothing silently if hw doesn't support */
	if (!ctl_mgr->single_flush_supported)
		return 0;

	if (!enable) {
		ctlx->pair = NULL;
		ctly->pair = NULL;
		mdp5_write(mdp5_kms, REG_MDP5_SPARE_0, 0);
		return 0;
	} else if ((ctlx->pair != NULL) || (ctly->pair != NULL)) {
		DRM_DEV_ERROR(ctl_mgr->dev->dev, "CTLs already paired\n");
		return -EINVAL;
	} else if (!(ctlx->status & ctly->status & CTL_STAT_BOOKED)) {
		DRM_DEV_ERROR(ctl_mgr->dev->dev, "Only pair booked CTLs\n");
		return -EINVAL;
	}

	ctlx->pair = ctly;
	ctly->pair = ctlx;

	mdp5_write(mdp5_kms, REG_MDP5_SPARE_0,
		   MDP5_SPARE_0_SPLIT_DPL_SINGLE_FLUSH_EN);

	return 0;
}