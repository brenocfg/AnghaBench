#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wil6210_vif {int dummy; } ;
struct wil6210_priv {int /*<<< orphan*/  vif_mutex; struct wil6210_vif** vifs; } ;
struct seq_file {struct wil6210_priv* private; } ;

/* Variables and functions */
 int GET_MAX_VIFS (struct wil6210_priv*) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 int /*<<< orphan*/  wil_link_stats_debugfs_show_vif (struct wil6210_vif*,struct seq_file*) ; 

__attribute__((used)) static int wil_link_stats_debugfs_show(struct seq_file *s, void *data)
{
	struct wil6210_priv *wil = s->private;
	struct wil6210_vif *vif;
	int i, rc;

	rc = mutex_lock_interruptible(&wil->vif_mutex);
	if (rc)
		return rc;

	/* iterate over all MIDs and show per-cid statistics. Then show the
	 * global statistics
	 */
	for (i = 0; i < GET_MAX_VIFS(wil); i++) {
		vif = wil->vifs[i];

		seq_printf(s, "MID %d ", i);
		if (!vif) {
			seq_puts(s, "unused\n");
			continue;
		}

		wil_link_stats_debugfs_show_vif(vif, s);
	}

	mutex_unlock(&wil->vif_mutex);

	return 0;
}