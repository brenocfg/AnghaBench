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
struct hisi_sas_itct {int dummy; } ;
struct hisi_hba {struct hisi_sas_itct* itct; TYPE_1__* hw; void* debugfs_itct; void* debugfs_itct_cache; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* read_iost_itct_cache ) (struct hisi_hba*,int /*<<< orphan*/ ,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  HISI_SAS_ITCT_CACHE ; 
 int HISI_SAS_MAX_ITCT_ENTRIES ; 
 int /*<<< orphan*/  memcpy (void*,struct hisi_sas_itct*,int) ; 
 int /*<<< orphan*/  stub1 (struct hisi_hba*,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void hisi_sas_debugfs_snapshot_itct_reg(struct hisi_hba *hisi_hba)
{
	void *cachebuf = hisi_hba->debugfs_itct_cache;
	void *databuf = hisi_hba->debugfs_itct;
	struct hisi_sas_itct *itct;
	int i;

	hisi_hba->hw->read_iost_itct_cache(hisi_hba, HISI_SAS_ITCT_CACHE,
					   cachebuf);

	itct = hisi_hba->itct;

	for (i = 0; i < HISI_SAS_MAX_ITCT_ENTRIES; i++, itct++) {
		memcpy(databuf, itct, sizeof(struct hisi_sas_itct));
		databuf += sizeof(struct hisi_sas_itct);
	}
}