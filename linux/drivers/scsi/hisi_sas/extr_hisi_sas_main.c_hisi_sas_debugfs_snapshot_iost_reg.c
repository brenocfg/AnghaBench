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
struct hisi_sas_iost {int dummy; } ;
struct hisi_hba {struct hisi_sas_iost* iost; TYPE_1__* hw; void* debugfs_iost; void* debugfs_iost_cache; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read_iost_itct_cache ) (struct hisi_hba*,int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HISI_SAS_IOST_CACHE ; 
 int HISI_SAS_MAX_COMMANDS ; 
 int /*<<< orphan*/  memcpy (void*,struct hisi_sas_iost*,int) ; 
 int /*<<< orphan*/  stub1 (struct hisi_hba*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void hisi_sas_debugfs_snapshot_iost_reg(struct hisi_hba *hisi_hba)
{
	int max_command_entries = HISI_SAS_MAX_COMMANDS;
	void *cachebuf = hisi_hba->debugfs_iost_cache;
	void *databuf = hisi_hba->debugfs_iost;
	struct hisi_sas_iost *iost;
	int i;

	hisi_hba->hw->read_iost_itct_cache(hisi_hba, HISI_SAS_IOST_CACHE,
					   cachebuf);

	iost = hisi_hba->iost;

	for (i = 0; i < max_command_entries; i++, iost++) {
		memcpy(databuf, iost, sizeof(struct hisi_sas_iost));
		databuf += sizeof(struct hisi_sas_iost);
	}
}