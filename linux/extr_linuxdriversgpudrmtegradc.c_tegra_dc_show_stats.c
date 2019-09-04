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
struct TYPE_4__ {int /*<<< orphan*/  overflow; int /*<<< orphan*/  underflow; int /*<<< orphan*/  vblank; int /*<<< orphan*/  frames; } ;
struct tegra_dc {TYPE_2__ stats; } ;
struct seq_file {struct drm_info_node* private; } ;
struct drm_info_node {TYPE_1__* info_ent; } ;
struct TYPE_3__ {struct tegra_dc* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tegra_dc_show_stats(struct seq_file *s, void *data)
{
	struct drm_info_node *node = s->private;
	struct tegra_dc *dc = node->info_ent->data;

	seq_printf(s, "frames: %lu\n", dc->stats.frames);
	seq_printf(s, "vblank: %lu\n", dc->stats.vblank);
	seq_printf(s, "underflow: %lu\n", dc->stats.underflow);
	seq_printf(s, "overflow: %lu\n", dc->stats.overflow);

	return 0;
}