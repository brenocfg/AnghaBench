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
typedef  int /*<<< orphan*/  u32 ;
struct hisi_sas_itct {int /*<<< orphan*/  qw0; } ;
struct hisi_sas_device {size_t device_id; } ;
struct hisi_hba {struct hisi_sas_itct* itct; } ;

/* Variables and functions */
 int /*<<< orphan*/  CFG_AGING_TIME ; 
 int /*<<< orphan*/  CFG_AGING_TIME_ITCT_REL_MSK ; 
 size_t ITCT_HDR_VALID_MSK ; 
 int /*<<< orphan*/  cpu_to_le64 (size_t) ; 
 int /*<<< orphan*/  hisi_sas_read32 (struct hisi_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_write32 (struct hisi_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void clear_itct_v1_hw(struct hisi_hba *hisi_hba,
			      struct hisi_sas_device *sas_dev)
{
	u64 dev_id = sas_dev->device_id;
	struct hisi_sas_itct *itct = &hisi_hba->itct[dev_id];
	u64 qw0;
	u32 reg_val = hisi_sas_read32(hisi_hba, CFG_AGING_TIME);

	reg_val |= CFG_AGING_TIME_ITCT_REL_MSK;
	hisi_sas_write32(hisi_hba, CFG_AGING_TIME, reg_val);

	/* free itct */
	udelay(1);
	reg_val = hisi_sas_read32(hisi_hba, CFG_AGING_TIME);
	reg_val &= ~CFG_AGING_TIME_ITCT_REL_MSK;
	hisi_sas_write32(hisi_hba, CFG_AGING_TIME, reg_val);

	qw0 = le64_to_cpu(itct->qw0);
	qw0 &= ~ITCT_HDR_VALID_MSK;
	itct->qw0 = cpu_to_le64(qw0);
}