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
typedef  int /*<<< orphan*/  u16 ;
struct bnxt {int flags; int /*<<< orphan*/  dev; int /*<<< orphan*/  rsscos_nr_ctxs; int /*<<< orphan*/  rx_nr_rings; } ;

/* Variables and functions */
 int BNXT_FLAG_AGG_RINGS ; 
 int DIV_ROUND_UP (int /*<<< orphan*/ ,int) ; 
 int ENOMEM ; 
 int bnxt_hwrm_vnic_cfg (struct bnxt*,int /*<<< orphan*/ ) ; 
 int bnxt_hwrm_vnic_ctx_alloc (struct bnxt*,int /*<<< orphan*/ ,int) ; 
 int bnxt_hwrm_vnic_set_hds (struct bnxt*,int /*<<< orphan*/ ) ; 
 int bnxt_hwrm_vnic_set_rss_p5 (struct bnxt*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,...) ; 

__attribute__((used)) static int __bnxt_setup_vnic_p5(struct bnxt *bp, u16 vnic_id)
{
	int rc, i, nr_ctxs;

	nr_ctxs = DIV_ROUND_UP(bp->rx_nr_rings, 64);
	for (i = 0; i < nr_ctxs; i++) {
		rc = bnxt_hwrm_vnic_ctx_alloc(bp, vnic_id, i);
		if (rc) {
			netdev_err(bp->dev, "hwrm vnic %d ctx %d alloc failure rc: %x\n",
				   vnic_id, i, rc);
			break;
		}
		bp->rsscos_nr_ctxs++;
	}
	if (i < nr_ctxs)
		return -ENOMEM;

	rc = bnxt_hwrm_vnic_set_rss_p5(bp, vnic_id, true);
	if (rc) {
		netdev_err(bp->dev, "hwrm vnic %d set rss failure rc: %d\n",
			   vnic_id, rc);
		return rc;
	}
	rc = bnxt_hwrm_vnic_cfg(bp, vnic_id);
	if (rc) {
		netdev_err(bp->dev, "hwrm vnic %d cfg failure rc: %x\n",
			   vnic_id, rc);
		return rc;
	}
	if (bp->flags & BNXT_FLAG_AGG_RINGS) {
		rc = bnxt_hwrm_vnic_set_hds(bp, vnic_id);
		if (rc) {
			netdev_err(bp->dev, "hwrm vnic %d set hds failure rc: %x\n",
				   vnic_id, rc);
		}
	}
	return rc;
}