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
struct hwrm_func_cfg_input {int /*<<< orphan*/  enables; int /*<<< orphan*/  member_0; } ;
struct TYPE_2__ {int resv_tx_rings; } ;
struct bnxt {int hwrm_spec_code; TYPE_1__ hw_resc; } ;
typedef  int /*<<< orphan*/  req ;

/* Variables and functions */
 int /*<<< orphan*/  HWRM_CMD_TIMEOUT ; 
 int /*<<< orphan*/  __bnxt_hwrm_reserve_pf_rings (struct bnxt*,struct hwrm_func_cfg_input*,int,int,int,int,int,int) ; 
 int bnxt_hwrm_get_rings (struct bnxt*) ; 
 int hwrm_send_message (struct bnxt*,struct hwrm_func_cfg_input*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bnxt_hwrm_reserve_pf_rings(struct bnxt *bp, int tx_rings, int rx_rings,
			   int ring_grps, int cp_rings, int stats, int vnics)
{
	struct hwrm_func_cfg_input req = {0};
	int rc;

	__bnxt_hwrm_reserve_pf_rings(bp, &req, tx_rings, rx_rings, ring_grps,
				     cp_rings, stats, vnics);
	if (!req.enables)
		return 0;

	rc = hwrm_send_message(bp, &req, sizeof(req), HWRM_CMD_TIMEOUT);
	if (rc)
		return rc;

	if (bp->hwrm_spec_code < 0x10601)
		bp->hw_resc.resv_tx_rings = tx_rings;

	rc = bnxt_hwrm_get_rings(bp);
	return rc;
}