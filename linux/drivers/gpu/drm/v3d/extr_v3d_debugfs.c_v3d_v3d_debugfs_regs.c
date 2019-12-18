#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct v3d_dev {int ver; int cores; } ;
struct seq_file {scalar_t__ private; } ;
struct drm_info_node {TYPE_1__* minor; } ;
struct drm_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  reg; int /*<<< orphan*/  name; } ;
struct TYPE_7__ {struct drm_device* dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_2__*) ; 
 int /*<<< orphan*/  V3D_CORE_READ (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V3D_GCA_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  V3D_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 struct v3d_dev* to_v3d_dev (struct drm_device*) ; 
 TYPE_2__* v3d_core_reg_defs ; 
 TYPE_2__* v3d_csd_reg_defs ; 
 TYPE_2__* v3d_gca_reg_defs ; 
 scalar_t__ v3d_has_csd (struct v3d_dev*) ; 
 TYPE_2__* v3d_hub_reg_defs ; 

__attribute__((used)) static int v3d_v3d_debugfs_regs(struct seq_file *m, void *unused)
{
	struct drm_info_node *node = (struct drm_info_node *)m->private;
	struct drm_device *dev = node->minor->dev;
	struct v3d_dev *v3d = to_v3d_dev(dev);
	int i, core;

	for (i = 0; i < ARRAY_SIZE(v3d_hub_reg_defs); i++) {
		seq_printf(m, "%s (0x%04x): 0x%08x\n",
			   v3d_hub_reg_defs[i].name, v3d_hub_reg_defs[i].reg,
			   V3D_READ(v3d_hub_reg_defs[i].reg));
	}

	if (v3d->ver < 41) {
		for (i = 0; i < ARRAY_SIZE(v3d_gca_reg_defs); i++) {
			seq_printf(m, "%s (0x%04x): 0x%08x\n",
				   v3d_gca_reg_defs[i].name,
				   v3d_gca_reg_defs[i].reg,
				   V3D_GCA_READ(v3d_gca_reg_defs[i].reg));
		}
	}

	for (core = 0; core < v3d->cores; core++) {
		for (i = 0; i < ARRAY_SIZE(v3d_core_reg_defs); i++) {
			seq_printf(m, "core %d %s (0x%04x): 0x%08x\n",
				   core,
				   v3d_core_reg_defs[i].name,
				   v3d_core_reg_defs[i].reg,
				   V3D_CORE_READ(core,
						 v3d_core_reg_defs[i].reg));
		}

		if (v3d_has_csd(v3d)) {
			for (i = 0; i < ARRAY_SIZE(v3d_csd_reg_defs); i++) {
				seq_printf(m, "core %d %s (0x%04x): 0x%08x\n",
					   core,
					   v3d_csd_reg_defs[i].name,
					   v3d_csd_reg_defs[i].reg,
					   V3D_CORE_READ(core,
							 v3d_csd_reg_defs[i].reg));
			}
		}
	}

	return 0;
}