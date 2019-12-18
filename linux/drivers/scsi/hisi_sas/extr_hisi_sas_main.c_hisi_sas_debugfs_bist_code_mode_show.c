#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct seq_file {struct hisi_hba* private; } ;
struct hisi_hba {scalar_t__ debugfs_bist_code_mode; } ;
struct TYPE_3__ {scalar_t__ value; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* hisi_sas_debugfs_loop_code_mode ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int hisi_sas_debugfs_bist_code_mode_show(struct seq_file *s, void *p)
{
	struct hisi_hba *hisi_hba = s->private;
	int i;

	for (i = 0; i < ARRAY_SIZE(hisi_sas_debugfs_loop_code_mode); i++) {
		int match = (hisi_hba->debugfs_bist_code_mode ==
			     hisi_sas_debugfs_loop_code_mode[i].value);

		seq_printf(s, "%s%s%s ", match ? "[" : "",
			   hisi_sas_debugfs_loop_code_mode[i].name,
			   match ? "]" : "");
	}
	seq_puts(s, "\n");

	return 0;
}