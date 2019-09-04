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
struct bnxt {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int bnxt_alloc_rfs_vnics(struct bnxt *bp)
{
#ifdef CONFIG_RFS_ACCEL
	int i, rc = 0;

	for (i = 0; i < bp->rx_nr_rings; i++) {
		struct bnxt_vnic_info *vnic;
		u16 vnic_id = i + 1;
		u16 ring_id = i;

		if (vnic_id >= bp->nr_vnics)
			break;

		vnic = &bp->vnic_info[vnic_id];
		vnic->flags |= BNXT_VNIC_RFS_FLAG;
		if (bp->flags & BNXT_FLAG_NEW_RSS_CAP)
			vnic->flags |= BNXT_VNIC_RFS_NEW_RSS_FLAG;
		rc = bnxt_hwrm_vnic_alloc(bp, vnic_id, ring_id, 1);
		if (rc) {
			netdev_err(bp->dev, "hwrm vnic %d alloc failure rc: %x\n",
				   vnic_id, rc);
			break;
		}
		rc = bnxt_setup_vnic(bp, vnic_id);
		if (rc)
			break;
	}
	return rc;
#else
	return 0;
#endif
}