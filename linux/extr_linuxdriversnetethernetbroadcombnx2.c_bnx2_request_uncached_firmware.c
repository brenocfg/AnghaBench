#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  rv2p; } ;
struct TYPE_9__ {int /*<<< orphan*/  rv2p; } ;
struct bnx2_rv2p_fw_file {TYPE_3__ proc2; TYPE_2__ proc1; } ;
struct bnx2_mips_fw_file {int /*<<< orphan*/  txp; int /*<<< orphan*/  tpat; int /*<<< orphan*/  rxp; int /*<<< orphan*/  cp; int /*<<< orphan*/  com; } ;
struct bnx2 {TYPE_4__* mips_firmware; TYPE_4__* rv2p_firmware; TYPE_1__* pdev; } ;
struct TYPE_11__ {int size; scalar_t__ data; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ BNX2_CHIP (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_5709 ; 
 scalar_t__ BNX2_CHIP_ID (struct bnx2*) ; 
 scalar_t__ BNX2_CHIP_ID_5709_A0 ; 
 scalar_t__ BNX2_CHIP_ID_5709_A1 ; 
 int EINVAL ; 
 char* FW_MIPS_FILE_06 ; 
 char* FW_MIPS_FILE_09 ; 
 char* FW_RV2P_FILE_06 ; 
 char* FW_RV2P_FILE_09 ; 
 char* FW_RV2P_FILE_09_Ax ; 
 scalar_t__ check_fw_section (TYPE_4__*,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ check_mips_fw_entry (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  release_firmware (TYPE_4__*) ; 
 int request_firmware (TYPE_4__**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int bnx2_request_uncached_firmware(struct bnx2 *bp)
{
	const char *mips_fw_file, *rv2p_fw_file;
	const struct bnx2_mips_fw_file *mips_fw;
	const struct bnx2_rv2p_fw_file *rv2p_fw;
	int rc;

	if (BNX2_CHIP(bp) == BNX2_CHIP_5709) {
		mips_fw_file = FW_MIPS_FILE_09;
		if ((BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5709_A0) ||
		    (BNX2_CHIP_ID(bp) == BNX2_CHIP_ID_5709_A1))
			rv2p_fw_file = FW_RV2P_FILE_09_Ax;
		else
			rv2p_fw_file = FW_RV2P_FILE_09;
	} else {
		mips_fw_file = FW_MIPS_FILE_06;
		rv2p_fw_file = FW_RV2P_FILE_06;
	}

	rc = request_firmware(&bp->mips_firmware, mips_fw_file, &bp->pdev->dev);
	if (rc) {
		pr_err("Can't load firmware file \"%s\"\n", mips_fw_file);
		goto out;
	}

	rc = request_firmware(&bp->rv2p_firmware, rv2p_fw_file, &bp->pdev->dev);
	if (rc) {
		pr_err("Can't load firmware file \"%s\"\n", rv2p_fw_file);
		goto err_release_mips_firmware;
	}
	mips_fw = (const struct bnx2_mips_fw_file *) bp->mips_firmware->data;
	rv2p_fw = (const struct bnx2_rv2p_fw_file *) bp->rv2p_firmware->data;
	if (bp->mips_firmware->size < sizeof(*mips_fw) ||
	    check_mips_fw_entry(bp->mips_firmware, &mips_fw->com) ||
	    check_mips_fw_entry(bp->mips_firmware, &mips_fw->cp) ||
	    check_mips_fw_entry(bp->mips_firmware, &mips_fw->rxp) ||
	    check_mips_fw_entry(bp->mips_firmware, &mips_fw->tpat) ||
	    check_mips_fw_entry(bp->mips_firmware, &mips_fw->txp)) {
		pr_err("Firmware file \"%s\" is invalid\n", mips_fw_file);
		rc = -EINVAL;
		goto err_release_firmware;
	}
	if (bp->rv2p_firmware->size < sizeof(*rv2p_fw) ||
	    check_fw_section(bp->rv2p_firmware, &rv2p_fw->proc1.rv2p, 8, true) ||
	    check_fw_section(bp->rv2p_firmware, &rv2p_fw->proc2.rv2p, 8, true)) {
		pr_err("Firmware file \"%s\" is invalid\n", rv2p_fw_file);
		rc = -EINVAL;
		goto err_release_firmware;
	}
out:
	return rc;

err_release_firmware:
	release_firmware(bp->rv2p_firmware);
	bp->rv2p_firmware = NULL;
err_release_mips_firmware:
	release_firmware(bp->mips_firmware);
	goto out;
}