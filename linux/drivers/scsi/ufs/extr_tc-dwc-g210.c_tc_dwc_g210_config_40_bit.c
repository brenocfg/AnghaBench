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
struct ufs_hba {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  UIC_ARG_MIB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VS_DEBUGOMC ; 
 int /*<<< orphan*/  VS_MPHYCFGUPDT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*) ; 
 int tc_dwc_g210_setup_40bit_rmmi (struct ufs_hba*) ; 
 int ufshcd_dme_set (struct ufs_hba*,int /*<<< orphan*/ ,int) ; 

int tc_dwc_g210_config_40_bit(struct ufs_hba *hba)
{
	int ret = 0;

	dev_info(hba->dev, "Configuring Test Chip 40-bit RMMI\n");
	ret = tc_dwc_g210_setup_40bit_rmmi(hba);
	if (ret) {
		dev_err(hba->dev, "Configuration failed\n");
		goto out;
	}

	/* To write Shadow register bank to effective configuration block */
	ret = ufshcd_dme_set(hba, UIC_ARG_MIB(VS_MPHYCFGUPDT), 0x01);
	if (ret)
		goto out;

	/* To configure Debug OMC */
	ret = ufshcd_dme_set(hba, UIC_ARG_MIB(VS_DEBUGOMC), 0x01);

out:
	return ret;
}