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
typedef  size_t u64 ;
typedef  int u32 ;
struct hisi_sas_itct {int dummy; } ;
struct hisi_sas_device {size_t device_id; int /*<<< orphan*/ * completion; } ;
struct hisi_hba {struct hisi_sas_itct* itct; } ;

/* Variables and functions */
 int /*<<< orphan*/  DECLARE_COMPLETION_ONSTACK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENT_INT_SRC3 ; 
 int ENT_INT_SRC3_ITC_INT_MSK ; 
 int /*<<< orphan*/  ITCT_CLR ; 
 size_t ITCT_CLR_EN_MSK ; 
 size_t ITCT_DEV_MSK ; 
 int /*<<< orphan*/  completion ; 
 int hisi_sas_read32 (struct hisi_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_write32 (struct hisi_hba*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct hisi_sas_itct*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clear_itct_v3_hw(struct hisi_hba *hisi_hba,
			      struct hisi_sas_device *sas_dev)
{
	DECLARE_COMPLETION_ONSTACK(completion);
	u64 dev_id = sas_dev->device_id;
	struct hisi_sas_itct *itct = &hisi_hba->itct[dev_id];
	u32 reg_val = hisi_sas_read32(hisi_hba, ENT_INT_SRC3);

	sas_dev->completion = &completion;

	/* clear the itct interrupt state */
	if (ENT_INT_SRC3_ITC_INT_MSK & reg_val)
		hisi_sas_write32(hisi_hba, ENT_INT_SRC3,
				 ENT_INT_SRC3_ITC_INT_MSK);

	/* clear the itct table */
	reg_val = ITCT_CLR_EN_MSK | (dev_id & ITCT_DEV_MSK);
	hisi_sas_write32(hisi_hba, ITCT_CLR, reg_val);

	wait_for_completion(sas_dev->completion);
	memset(itct, 0, sizeof(struct hisi_sas_itct));
}