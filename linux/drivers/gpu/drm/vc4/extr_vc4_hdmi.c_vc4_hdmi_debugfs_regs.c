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
struct vc4_hdmi {int /*<<< orphan*/  hd_regset; int /*<<< orphan*/  hdmi_regset; } ;
struct vc4_dev {struct vc4_hdmi* hdmi; } ;
struct seq_file {scalar_t__ private; } ;
struct drm_printer {int dummy; } ;
struct drm_info_node {TYPE_1__* minor; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {struct drm_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_print_regset32 (struct drm_printer*,int /*<<< orphan*/ *) ; 
 struct drm_printer drm_seq_file_printer (struct seq_file*) ; 
 struct vc4_dev* to_vc4_dev (struct drm_device*) ; 

__attribute__((used)) static int vc4_hdmi_debugfs_regs(struct seq_file *m, void *unused)
{
	struct drm_info_node *node = (struct drm_info_node *)m->private;
	struct drm_device *dev = node->minor->dev;
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	struct vc4_hdmi *hdmi = vc4->hdmi;
	struct drm_printer p = drm_seq_file_printer(m);

	drm_print_regset32(&p, &hdmi->hdmi_regset);
	drm_print_regset32(&p, &hdmi->hd_regset);

	return 0;
}