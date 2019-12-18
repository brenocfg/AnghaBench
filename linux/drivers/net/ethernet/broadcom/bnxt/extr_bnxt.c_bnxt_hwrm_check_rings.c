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
struct bnxt {int hwrm_spec_code; } ;

/* Variables and functions */
 scalar_t__ BNXT_PF (struct bnxt*) ; 
 int bnxt_hwrm_check_pf_rings (struct bnxt*,int,int,int,int,int,int) ; 
 int bnxt_hwrm_check_vf_rings (struct bnxt*,int,int,int,int,int,int) ; 

__attribute__((used)) static int bnxt_hwrm_check_rings(struct bnxt *bp, int tx_rings, int rx_rings,
				 int ring_grps, int cp_rings, int stats,
				 int vnics)
{
	if (bp->hwrm_spec_code < 0x10801)
		return 0;

	if (BNXT_PF(bp))
		return bnxt_hwrm_check_pf_rings(bp, tx_rings, rx_rings,
						ring_grps, cp_rings, stats,
						vnics);

	return bnxt_hwrm_check_vf_rings(bp, tx_rings, rx_rings, ring_grps,
					cp_rings, stats, vnics);
}