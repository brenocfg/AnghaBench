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
struct net_device {int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int GET_MAX_VIFS (struct wil6210_priv*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 struct net_device* vif_to_ndev (struct wil6210_vif*) ; 

__attribute__((used)) static int mids_show(struct seq_file *s, void *data)
{
	struct wil6210_priv *wil = s->private;
	struct wil6210_vif *vif;
	struct net_device *ndev;
	int i;

	mutex_lock(&wil->vif_mutex);
	for (i = 0; i < GET_MAX_VIFS(wil); i++) {
		vif = wil->vifs[i];

		if (vif) {
			ndev = vif_to_ndev(vif);
			seq_printf(s, "[%d] %pM %s\n", i, ndev->dev_addr,
				   ndev->name);
		} else {
			seq_printf(s, "[%d] unused\n", i);
		}
	}
	mutex_unlock(&wil->vif_mutex);

	return 0;
}