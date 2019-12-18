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
struct wmi_link_stats_basic {int dummy; } ;
struct wil6210_vif {scalar_t__ mid; int /*<<< orphan*/  fw_stats_tsf; int /*<<< orphan*/  fw_stats_ready; } ;
struct wil6210_priv {int max_assoc_sta; TYPE_1__* sta; } ;
struct seq_file {int dummy; } ;
struct TYPE_2__ {scalar_t__ status; scalar_t__ mid; struct wmi_link_stats_basic fw_stats_basic; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 struct wil6210_priv* vif_to_wil (struct wil6210_vif*) ; 
 int /*<<< orphan*/  wil_link_stats_print_basic (struct wil6210_vif*,struct seq_file*,struct wmi_link_stats_basic*) ; 
 scalar_t__ wil_sta_unused ; 

__attribute__((used)) static void wil_link_stats_debugfs_show_vif(struct wil6210_vif *vif,
					    struct seq_file *s)
{
	struct wil6210_priv *wil = vif_to_wil(vif);
	struct wmi_link_stats_basic *stats;
	int i;

	if (!vif->fw_stats_ready) {
		seq_puts(s, "no statistics\n");
		return;
	}

	seq_printf(s, "TSF %lld\n", vif->fw_stats_tsf);
	for (i = 0; i < wil->max_assoc_sta; i++) {
		if (wil->sta[i].status == wil_sta_unused)
			continue;
		if (wil->sta[i].mid != vif->mid)
			continue;

		stats = &wil->sta[i].fw_stats_basic;
		wil_link_stats_print_basic(vif, s, stats);
	}
}