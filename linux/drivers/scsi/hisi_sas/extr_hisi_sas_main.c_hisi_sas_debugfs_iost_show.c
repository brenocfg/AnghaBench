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
struct hisi_sas_iost {int /*<<< orphan*/  qw0; } ;
struct hisi_hba {struct hisi_sas_iost* debugfs_iost; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int HISI_SAS_MAX_COMMANDS ; 
 int /*<<< orphan*/  hisi_sas_show_row_64 (struct seq_file*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hisi_sas_debugfs_iost_show(struct seq_file *s, void *p)
{
	struct hisi_hba *hisi_hba = s->private;
	struct hisi_sas_iost *debugfs_iost = hisi_hba->debugfs_iost;
	int i, max_command_entries = HISI_SAS_MAX_COMMANDS;

	for (i = 0; i < max_command_entries; i++, debugfs_iost++) {
		__le64 *iost = &debugfs_iost->qw0;

		hisi_sas_show_row_64(s, i, sizeof(*debugfs_iost), iost);
	}

	return 0;
}