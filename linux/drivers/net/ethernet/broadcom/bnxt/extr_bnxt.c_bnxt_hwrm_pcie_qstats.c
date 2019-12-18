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
struct pcie_ctx_hw_stats {int dummy; } ;
struct hwrm_pcie_qstats_input {int /*<<< orphan*/  pcie_stat_host_addr; int /*<<< orphan*/  pcie_stat_size; int /*<<< orphan*/  member_0; } ;
struct bnxt {int flags; int /*<<< orphan*/  hw_pcie_stats_map; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int BNXT_FLAG_PCIE_STATS ; 
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  HWRM_PCIE_QSTATS ; 
 int /*<<< orphan*/  bnxt_hwrm_cmd_hdr_init (struct bnxt*,struct hwrm_pcie_qstats_input*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_pcie_qstats_input*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int bnxt_hwrm_pcie_qstats(struct bnxt *bp)
{
	struct hwrm_pcie_qstats_input req = {0};

	if (!(bp->flags & BNXT_FLAG_PCIE_STATS))
		return 0;

	bnxt_hwrm_cmd_hdr_init(bp, &req, HWRM_PCIE_QSTATS, -1, -1);
	req.pcie_stat_size = cpu_to_le16(sizeof(struct pcie_ctx_hw_stats));
	req.pcie_stat_host_addr = cpu_to_le64(bp->hw_pcie_stats_map);
	return hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
}