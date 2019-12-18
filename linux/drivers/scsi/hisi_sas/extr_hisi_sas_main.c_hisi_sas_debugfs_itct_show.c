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
struct hisi_sas_itct {int /*<<< orphan*/  qw0; } ;
struct hisi_hba {struct hisi_sas_itct* debugfs_itct; } ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int HISI_SAS_MAX_ITCT_ENTRIES ; 
 int /*<<< orphan*/  hisi_sas_show_row_64 (struct seq_file*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int hisi_sas_debugfs_itct_show(struct seq_file *s, void *p)
{
	int i;
	struct hisi_hba *hisi_hba = s->private;
	struct hisi_sas_itct *debugfs_itct = hisi_hba->debugfs_itct;

	for (i = 0; i < HISI_SAS_MAX_ITCT_ENTRIES; i++, debugfs_itct++) {
		__le64 *itct = &debugfs_itct->qw0;

		hisi_sas_show_row_64(s, i, sizeof(*debugfs_itct), itct);
	}

	return 0;
}