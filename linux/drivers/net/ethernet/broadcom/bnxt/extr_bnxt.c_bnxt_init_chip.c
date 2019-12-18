#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct bnxt_vnic_info {int uc_filter_count; int /*<<< orphan*/  rx_mask; scalar_t__ mc_list_count; } ;
struct bnxt {unsigned int rx_nr_rings; int flags; TYPE_1__* dev; struct bnxt_vnic_info* vnic_info; } ;
struct TYPE_4__ {int flags; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 scalar_t__ BNXT_CHIP_TYPE_NITRO_A0 (struct bnxt*) ; 
 int BNXT_FLAG_RFS ; 
 int BNXT_FLAG_TPA ; 
 scalar_t__ BNXT_VF (struct bnxt*) ; 
 int /*<<< orphan*/  CFA_L2_SET_RX_MASK_REQ_MASK_ALL_MCAST ; 
 int /*<<< orphan*/  CFA_L2_SET_RX_MASK_REQ_MASK_BCAST ; 
 int /*<<< orphan*/  CFA_L2_SET_RX_MASK_REQ_MASK_PROMISCUOUS ; 
 int IFF_ALLMULTI ; 
 int IFF_BROADCAST ; 
 int IFF_PROMISC ; 
 int bnxt_alloc_rfs_vnics (struct bnxt*) ; 
 int bnxt_cfg_rx_mode (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_hwrm_func_qcfg (struct bnxt*) ; 
 int /*<<< orphan*/  bnxt_hwrm_resource_free (struct bnxt*,int /*<<< orphan*/ ,int) ; 
 int bnxt_hwrm_ring_alloc (struct bnxt*) ; 
 int bnxt_hwrm_ring_grp_alloc (struct bnxt*) ; 
 int bnxt_hwrm_set_coal (struct bnxt*) ; 
 int bnxt_hwrm_set_vnic_filter (struct bnxt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int bnxt_hwrm_stat_ctx_alloc (struct bnxt*) ; 
 int bnxt_hwrm_vnic_alloc (struct bnxt*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  bnxt_mc_list_updated (struct bnxt*,int /*<<< orphan*/ *) ; 
 scalar_t__ bnxt_promisc_ok (struct bnxt*) ; 
 int bnxt_set_tpa (struct bnxt*,int) ; 
 int bnxt_setup_nitroa0_vnic (struct bnxt*) ; 
 int bnxt_setup_vnic (struct bnxt*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bnxt_update_vf_mac (struct bnxt*) ; 
 int /*<<< orphan*/  netdev_err (TYPE_1__*,char*,int) ; 
 int /*<<< orphan*/  netdev_update_features (TYPE_1__*) ; 
 int /*<<< orphan*/  netdev_warn (TYPE_1__*,char*,int) ; 

__attribute__((used)) static int bnxt_init_chip(struct bnxt *bp, bool irq_re_init)
{
	struct bnxt_vnic_info *vnic = &bp->vnic_info[0];
	int rc = 0;
	unsigned int rx_nr_rings = bp->rx_nr_rings;

	if (irq_re_init) {
		rc = bnxt_hwrm_stat_ctx_alloc(bp);
		if (rc) {
			netdev_err(bp->dev, "hwrm stat ctx alloc failure rc: %x\n",
				   rc);
			goto err_out;
		}
	}

	rc = bnxt_hwrm_ring_alloc(bp);
	if (rc) {
		netdev_err(bp->dev, "hwrm ring alloc failure rc: %x\n", rc);
		goto err_out;
	}

	rc = bnxt_hwrm_ring_grp_alloc(bp);
	if (rc) {
		netdev_err(bp->dev, "hwrm_ring_grp alloc failure: %x\n", rc);
		goto err_out;
	}

	if (BNXT_CHIP_TYPE_NITRO_A0(bp))
		rx_nr_rings--;

	/* default vnic 0 */
	rc = bnxt_hwrm_vnic_alloc(bp, 0, 0, rx_nr_rings);
	if (rc) {
		netdev_err(bp->dev, "hwrm vnic alloc failure rc: %x\n", rc);
		goto err_out;
	}

	rc = bnxt_setup_vnic(bp, 0);
	if (rc)
		goto err_out;

	if (bp->flags & BNXT_FLAG_RFS) {
		rc = bnxt_alloc_rfs_vnics(bp);
		if (rc)
			goto err_out;
	}

	if (bp->flags & BNXT_FLAG_TPA) {
		rc = bnxt_set_tpa(bp, true);
		if (rc)
			goto err_out;
	}

	if (BNXT_VF(bp))
		bnxt_update_vf_mac(bp);

	/* Filter for default vnic 0 */
	rc = bnxt_hwrm_set_vnic_filter(bp, 0, 0, bp->dev->dev_addr);
	if (rc) {
		netdev_err(bp->dev, "HWRM vnic filter failure rc: %x\n", rc);
		goto err_out;
	}
	vnic->uc_filter_count = 1;

	vnic->rx_mask = 0;
	if (bp->dev->flags & IFF_BROADCAST)
		vnic->rx_mask |= CFA_L2_SET_RX_MASK_REQ_MASK_BCAST;

	if ((bp->dev->flags & IFF_PROMISC) && bnxt_promisc_ok(bp))
		vnic->rx_mask |= CFA_L2_SET_RX_MASK_REQ_MASK_PROMISCUOUS;

	if (bp->dev->flags & IFF_ALLMULTI) {
		vnic->rx_mask |= CFA_L2_SET_RX_MASK_REQ_MASK_ALL_MCAST;
		vnic->mc_list_count = 0;
	} else {
		u32 mask = 0;

		bnxt_mc_list_updated(bp, &mask);
		vnic->rx_mask |= mask;
	}

	rc = bnxt_cfg_rx_mode(bp);
	if (rc)
		goto err_out;

	rc = bnxt_hwrm_set_coal(bp);
	if (rc)
		netdev_warn(bp->dev, "HWRM set coalescing failure rc: %x\n",
				rc);

	if (BNXT_CHIP_TYPE_NITRO_A0(bp)) {
		rc = bnxt_setup_nitroa0_vnic(bp);
		if (rc)
			netdev_err(bp->dev, "Special vnic setup failure for NS2 A0 rc: %x\n",
				   rc);
	}

	if (BNXT_VF(bp)) {
		bnxt_hwrm_func_qcfg(bp);
		netdev_update_features(bp->dev);
	}

	return 0;

err_out:
	bnxt_hwrm_resource_free(bp, 0, true);

	return rc;
}