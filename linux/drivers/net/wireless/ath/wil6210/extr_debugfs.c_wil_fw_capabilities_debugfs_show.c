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
struct wil6210_priv {int /*<<< orphan*/  fw_capabilities; } ;
struct seq_file {struct wil6210_priv* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  WMI_FW_CAPABILITY_MAX ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wil_fw_capabilities_debugfs_show(struct seq_file *s, void *data)
{
	struct wil6210_priv *wil = s->private;

	seq_printf(s, "fw_capabilities : %*pb\n", WMI_FW_CAPABILITY_MAX,
		   wil->fw_capabilities);

	return 0;
}