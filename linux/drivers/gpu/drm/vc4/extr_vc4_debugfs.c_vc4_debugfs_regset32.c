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
struct seq_file {scalar_t__ private; } ;
struct drm_printer {int dummy; } ;
struct drm_info_node {TYPE_1__* info_ent; } ;
struct debugfs_regset32 {int dummy; } ;
struct TYPE_2__ {struct debugfs_regset32* data; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_print_regset32 (struct drm_printer*,struct debugfs_regset32*) ; 
 struct drm_printer drm_seq_file_printer (struct seq_file*) ; 

__attribute__((used)) static int vc4_debugfs_regset32(struct seq_file *m, void *unused)
{
	struct drm_info_node *node = (struct drm_info_node *)m->private;
	struct debugfs_regset32 *regset = node->info_ent->data;
	struct drm_printer p = drm_seq_file_printer(m);

	drm_print_regset32(&p, regset);

	return 0;
}