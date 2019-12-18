#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {struct drm_crtc* crtc; } ;
struct TYPE_10__ {TYPE_2__ encoder; } ;
struct tegra_hdmi {TYPE_3__ output; } ;
struct seq_file {struct drm_info_node* private; } ;
struct drm_info_node {TYPE_4__* minor; TYPE_1__* info_ent; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {TYPE_5__* state; } ;
struct TYPE_13__ {unsigned int offset; int /*<<< orphan*/  name; } ;
struct TYPE_12__ {int /*<<< orphan*/  active; } ;
struct TYPE_11__ {struct drm_device* dev; } ;
struct TYPE_8__ {struct tegra_hdmi* data; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_6__*) ; 
 int EBUSY ; 
 int /*<<< orphan*/  drm_modeset_lock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (struct drm_device*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_hdmi_readl (struct tegra_hdmi*,unsigned int) ; 
 TYPE_6__* tegra_hdmi_regs ; 

__attribute__((used)) static int tegra_hdmi_show_regs(struct seq_file *s, void *data)
{
	struct drm_info_node *node = s->private;
	struct tegra_hdmi *hdmi = node->info_ent->data;
	struct drm_crtc *crtc = hdmi->output.encoder.crtc;
	struct drm_device *drm = node->minor->dev;
	unsigned int i;
	int err = 0;

	drm_modeset_lock_all(drm);

	if (!crtc || !crtc->state->active) {
		err = -EBUSY;
		goto unlock;
	}

	for (i = 0; i < ARRAY_SIZE(tegra_hdmi_regs); i++) {
		unsigned int offset = tegra_hdmi_regs[i].offset;

		seq_printf(s, "%-56s %#05x %08x\n", tegra_hdmi_regs[i].name,
			   offset, tegra_hdmi_readl(hdmi, offset));
	}

unlock:
	drm_modeset_unlock_all(drm);
	return err;
}