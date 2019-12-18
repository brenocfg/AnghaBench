#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {struct drm_crtc* crtc; } ;
struct TYPE_8__ {TYPE_2__ encoder; } ;
struct tegra_sor {TYPE_3__ output; } ;
struct seq_file {struct drm_info_node* private; } ;
struct drm_info_node {TYPE_4__* minor; TYPE_1__* info_ent; } ;
struct drm_device {int dummy; } ;
struct drm_crtc {TYPE_5__* state; } ;
struct TYPE_10__ {int /*<<< orphan*/  active; } ;
struct TYPE_9__ {struct drm_device* dev; } ;
struct TYPE_6__ {struct tegra_sor* data; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  SOR_CRCA ; 
 int /*<<< orphan*/  SOR_CRCA_RESET ; 
 int /*<<< orphan*/  SOR_CRCB ; 
 int /*<<< orphan*/  SOR_CRC_CNTRL ; 
 int /*<<< orphan*/  SOR_CRC_CNTRL_ENABLE ; 
 int /*<<< orphan*/  SOR_STATE1 ; 
 int /*<<< orphan*/  SOR_STATE_ASY_CRC_MODE_MASK ; 
 int /*<<< orphan*/  SOR_TEST ; 
 int /*<<< orphan*/  SOR_TEST_CRC_POST_SERIALIZE ; 
 int /*<<< orphan*/  drm_modeset_lock_all (struct drm_device*) ; 
 int /*<<< orphan*/  drm_modeset_unlock_all (struct drm_device*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int tegra_sor_crc_wait (struct tegra_sor*,int) ; 
 int /*<<< orphan*/  tegra_sor_readl (struct tegra_sor*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_sor_writel (struct tegra_sor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_sor_show_crc(struct seq_file *s, void *data)
{
	struct drm_info_node *node = s->private;
	struct tegra_sor *sor = node->info_ent->data;
	struct drm_crtc *crtc = sor->output.encoder.crtc;
	struct drm_device *drm = node->minor->dev;
	int err = 0;
	u32 value;

	drm_modeset_lock_all(drm);

	if (!crtc || !crtc->state->active) {
		err = -EBUSY;
		goto unlock;
	}

	value = tegra_sor_readl(sor, SOR_STATE1);
	value &= ~SOR_STATE_ASY_CRC_MODE_MASK;
	tegra_sor_writel(sor, value, SOR_STATE1);

	value = tegra_sor_readl(sor, SOR_CRC_CNTRL);
	value |= SOR_CRC_CNTRL_ENABLE;
	tegra_sor_writel(sor, value, SOR_CRC_CNTRL);

	value = tegra_sor_readl(sor, SOR_TEST);
	value &= ~SOR_TEST_CRC_POST_SERIALIZE;
	tegra_sor_writel(sor, value, SOR_TEST);

	err = tegra_sor_crc_wait(sor, 100);
	if (err < 0)
		goto unlock;

	tegra_sor_writel(sor, SOR_CRCA_RESET, SOR_CRCA);
	value = tegra_sor_readl(sor, SOR_CRCB);

	seq_printf(s, "%08x\n", value);

unlock:
	drm_modeset_unlock_all(drm);
	return err;
}