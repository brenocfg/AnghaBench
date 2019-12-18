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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int select_minor; int /*<<< orphan*/  select_major; } ;
struct ufs_qcom_host {TYPE_1__ testbus; } ;
struct ufs_hba {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMP_PREFIX_OFFSET ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  TSTBUS_UNIPRO ; 
 int /*<<< orphan*/  UFS_TEST_BUS ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_hex_dump (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  ufs_qcom_testbus_config (struct ufs_qcom_host*) ; 
 struct ufs_qcom_host* ufshcd_get_variant (struct ufs_hba*) ; 
 int /*<<< orphan*/  ufshcd_readl (struct ufs_hba*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ufs_qcom_print_unipro_testbus(struct ufs_hba *hba)
{
	struct ufs_qcom_host *host = ufshcd_get_variant(hba);
	u32 *testbus = NULL;
	int i, nminor = 256, testbus_len = nminor * sizeof(u32);

	testbus = kmalloc(testbus_len, GFP_KERNEL);
	if (!testbus)
		return;

	host->testbus.select_major = TSTBUS_UNIPRO;
	for (i = 0; i < nminor; i++) {
		host->testbus.select_minor = i;
		ufs_qcom_testbus_config(host);
		testbus[i] = ufshcd_readl(hba, UFS_TEST_BUS);
	}
	print_hex_dump(KERN_ERR, "UNIPRO_TEST_BUS ", DUMP_PREFIX_OFFSET,
			16, 4, testbus, testbus_len, false);
	kfree(testbus);
}