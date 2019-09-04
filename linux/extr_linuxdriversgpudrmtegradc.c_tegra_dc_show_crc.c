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
typedef  int u32 ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; TYPE_2__* state; } ;
struct tegra_dc {TYPE_3__ base; } ;
struct seq_file {struct drm_info_node* private; } ;
struct drm_info_node {TYPE_1__* info_ent; } ;
struct TYPE_5__ {int /*<<< orphan*/  active; } ;
struct TYPE_4__ {struct tegra_dc* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DC_COM_CRC_CHECKSUM ; 
 int /*<<< orphan*/  DC_COM_CRC_CONTROL ; 
 int DC_COM_CRC_CONTROL_ACTIVE_DATA ; 
 int DC_COM_CRC_CONTROL_ENABLE ; 
 int EBUSY ; 
 int /*<<< orphan*/  drm_crtc_wait_one_vblank (TYPE_3__*) ; 
 int /*<<< orphan*/  drm_modeset_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  drm_modeset_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  tegra_dc_commit (struct tegra_dc*) ; 
 int tegra_dc_readl (struct tegra_dc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tegra_dc_writel (struct tegra_dc*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_dc_show_crc(struct seq_file *s, void *data)
{
	struct drm_info_node *node = s->private;
	struct tegra_dc *dc = node->info_ent->data;
	int err = 0;
	u32 value;

	drm_modeset_lock(&dc->base.mutex, NULL);

	if (!dc->base.state->active) {
		err = -EBUSY;
		goto unlock;
	}

	value = DC_COM_CRC_CONTROL_ACTIVE_DATA | DC_COM_CRC_CONTROL_ENABLE;
	tegra_dc_writel(dc, value, DC_COM_CRC_CONTROL);
	tegra_dc_commit(dc);

	drm_crtc_wait_one_vblank(&dc->base);
	drm_crtc_wait_one_vblank(&dc->base);

	value = tegra_dc_readl(dc, DC_COM_CRC_CHECKSUM);
	seq_printf(s, "%08x\n", value);

	tegra_dc_writel(dc, 0, DC_COM_CRC_CONTROL);

unlock:
	drm_modeset_unlock(&dc->base.mutex);
	return err;
}