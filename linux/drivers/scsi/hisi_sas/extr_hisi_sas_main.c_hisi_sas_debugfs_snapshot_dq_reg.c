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
struct hisi_sas_cmd_hdr {int dummy; } ;
struct hisi_hba {int queue_count; struct hisi_sas_cmd_hdr** cmd_hdr; struct hisi_sas_cmd_hdr** debugfs_cmd_hdr; } ;

/* Variables and functions */
 int HISI_SAS_QUEUE_SLOTS ; 
 int /*<<< orphan*/  memcpy (struct hisi_sas_cmd_hdr*,struct hisi_sas_cmd_hdr*,int) ; 

__attribute__((used)) static void hisi_sas_debugfs_snapshot_dq_reg(struct hisi_hba *hisi_hba)
{
	int queue_entry_size = sizeof(struct hisi_sas_cmd_hdr);
	int i;

	for (i = 0; i < hisi_hba->queue_count; i++) {
		struct hisi_sas_cmd_hdr	*debugfs_cmd_hdr, *cmd_hdr;
		int j;

		debugfs_cmd_hdr = hisi_hba->debugfs_cmd_hdr[i];
		cmd_hdr = hisi_hba->cmd_hdr[i];

		for (j = 0; j < HISI_SAS_QUEUE_SLOTS; j++)
			memcpy(&debugfs_cmd_hdr[j], &cmd_hdr[j],
			       queue_entry_size);
	}
}