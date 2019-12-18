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
struct seq_file {struct hisi_hba* private; } ;
struct hisi_hba {int /*<<< orphan*/  debugfs_bist_enable; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hisi_sas_debugfs_bist_enable_show(struct seq_file *s, void *p)
{
	struct hisi_hba *hisi_hba = s->private;

	seq_printf(s, "%d\n", hisi_hba->debugfs_bist_enable);

	return 0;
}