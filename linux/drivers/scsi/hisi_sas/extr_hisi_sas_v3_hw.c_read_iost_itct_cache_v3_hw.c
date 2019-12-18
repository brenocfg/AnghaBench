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
typedef  int u32 ;
struct hisi_hba {int dummy; } ;
typedef  enum hisi_sas_debugfs_cache_type { ____Placeholder_hisi_sas_debugfs_cache_type } hisi_sas_debugfs_cache_type ;

/* Variables and functions */
 int HISI_SAS_IOST_ITCT_CACHE_DW_SZ ; 
 int HISI_SAS_IOST_ITCT_CACHE_NUM ; 
 int /*<<< orphan*/  TAB_DFX ; 
 int /*<<< orphan*/  TAB_RD_TYPE ; 
 int hisi_sas_read32 (struct hisi_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hisi_sas_write32 (struct hisi_hba*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static void read_iost_itct_cache_v3_hw(struct hisi_hba *hisi_hba,
				       enum hisi_sas_debugfs_cache_type type,
				       u32 *cache)
{
	u32 cache_dw_size = HISI_SAS_IOST_ITCT_CACHE_DW_SZ *
			    HISI_SAS_IOST_ITCT_CACHE_NUM;
	u32 *buf = cache;
	u32 i, val;

	hisi_sas_write32(hisi_hba, TAB_RD_TYPE, type);

	for (i = 0; i < HISI_SAS_IOST_ITCT_CACHE_DW_SZ; i++) {
		val = hisi_sas_read32(hisi_hba, TAB_DFX);
		if (val == 0xffffffff)
			break;
	}

	if (val != 0xffffffff) {
		pr_err("Issue occur when reading IOST/ITCT cache!\n");
		return;
	}

	memset(buf, 0, cache_dw_size * 4);
	buf[0] = val;

	for (i = 1; i < cache_dw_size; i++)
		buf[i] = hisi_sas_read32(hisi_hba, TAB_DFX);
}