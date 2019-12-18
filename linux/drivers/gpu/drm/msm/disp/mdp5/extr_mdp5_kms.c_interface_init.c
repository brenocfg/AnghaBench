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
struct mdp5_kms {int /*<<< orphan*/  num_intfs; struct mdp5_interface** intfs; int /*<<< orphan*/  cfg; struct drm_device* dev; } ;
struct mdp5_interface {int num; int type; int /*<<< orphan*/  idx; int /*<<< orphan*/  mode; } ;
struct TYPE_2__ {int* connect; } ;
struct mdp5_cfg_hw {TYPE_1__ intf; } ;
struct drm_device {int /*<<< orphan*/  dev; } ;
typedef  enum mdp5_intf_type { ____Placeholder_mdp5_intf_type } mdp5_intf_type ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int const INTF_DISABLED ; 
 int /*<<< orphan*/  MDP5_INTF_MODE_NONE ; 
 struct mdp5_interface* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct mdp5_cfg_hw* mdp5_cfg_get_hw_config (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int interface_init(struct mdp5_kms *mdp5_kms)
{
	struct drm_device *dev = mdp5_kms->dev;
	const struct mdp5_cfg_hw *hw_cfg;
	const enum mdp5_intf_type *intf_types;
	int i;

	hw_cfg = mdp5_cfg_get_hw_config(mdp5_kms->cfg);
	intf_types = hw_cfg->intf.connect;

	for (i = 0; i < ARRAY_SIZE(hw_cfg->intf.connect); i++) {
		struct mdp5_interface *intf;

		if (intf_types[i] == INTF_DISABLED)
			continue;

		intf = kzalloc(sizeof(*intf), GFP_KERNEL);
		if (!intf) {
			DRM_DEV_ERROR(dev->dev, "failed to construct INTF%d\n", i);
			return -ENOMEM;
		}

		intf->num = i;
		intf->type = intf_types[i];
		intf->mode = MDP5_INTF_MODE_NONE;
		intf->idx = mdp5_kms->num_intfs;
		mdp5_kms->intfs[mdp5_kms->num_intfs++] = intf;
	}

	return 0;
}