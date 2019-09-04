#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bnx2_rv2p_fw_file {int /*<<< orphan*/  proc2; int /*<<< orphan*/  proc1; } ;
struct bnx2_mips_fw_file {int /*<<< orphan*/  cp; int /*<<< orphan*/  com; int /*<<< orphan*/  tpat; int /*<<< orphan*/  txp; int /*<<< orphan*/  rxp; } ;
struct bnx2 {TYPE_2__* rv2p_firmware; TYPE_1__* mips_firmware; } ;
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_3__ {scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  RV2P_PROC1 ; 
 int /*<<< orphan*/  RV2P_PROC2 ; 
 int /*<<< orphan*/  cpu_reg_com ; 
 int /*<<< orphan*/  cpu_reg_cp ; 
 int /*<<< orphan*/  cpu_reg_rxp ; 
 int /*<<< orphan*/  cpu_reg_tpat ; 
 int /*<<< orphan*/  cpu_reg_txp ; 
 int load_cpu_fw (struct bnx2*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  load_rv2p_fw (struct bnx2*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bnx2_init_cpus(struct bnx2 *bp)
{
	const struct bnx2_mips_fw_file *mips_fw =
		(const struct bnx2_mips_fw_file *) bp->mips_firmware->data;
	const struct bnx2_rv2p_fw_file *rv2p_fw =
		(const struct bnx2_rv2p_fw_file *) bp->rv2p_firmware->data;
	int rc;

	/* Initialize the RV2P processor. */
	load_rv2p_fw(bp, RV2P_PROC1, &rv2p_fw->proc1);
	load_rv2p_fw(bp, RV2P_PROC2, &rv2p_fw->proc2);

	/* Initialize the RX Processor. */
	rc = load_cpu_fw(bp, &cpu_reg_rxp, &mips_fw->rxp);
	if (rc)
		goto init_cpu_err;

	/* Initialize the TX Processor. */
	rc = load_cpu_fw(bp, &cpu_reg_txp, &mips_fw->txp);
	if (rc)
		goto init_cpu_err;

	/* Initialize the TX Patch-up Processor. */
	rc = load_cpu_fw(bp, &cpu_reg_tpat, &mips_fw->tpat);
	if (rc)
		goto init_cpu_err;

	/* Initialize the Completion Processor. */
	rc = load_cpu_fw(bp, &cpu_reg_com, &mips_fw->com);
	if (rc)
		goto init_cpu_err;

	/* Initialize the Command Processor. */
	rc = load_cpu_fw(bp, &cpu_reg_cp, &mips_fw->cp);

init_cpu_err:
	return rc;
}