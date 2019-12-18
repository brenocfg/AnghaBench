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
struct seq_file {int dummy; } ;
struct hisi_sas_dq {size_t id; struct hisi_hba* hisi_hba; } ;
struct hisi_sas_cmd_hdr {int dummy; } ;
struct hisi_hba {void** debugfs_cmd_hdr; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  hisi_sas_show_row_32 (struct seq_file*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void hisi_sas_dq_show_slot(struct seq_file *s, int slot, void *dq_ptr)
{
	struct hisi_sas_dq *dq = dq_ptr;
	struct hisi_hba *hisi_hba = dq->hisi_hba;
	void *cmd_queue = hisi_hba->debugfs_cmd_hdr[dq->id];
	__le32 *cmd_hdr = cmd_queue +
		sizeof(struct hisi_sas_cmd_hdr) * slot;

	hisi_sas_show_row_32(s, slot, sizeof(struct hisi_sas_cmd_hdr), cmd_hdr);
}