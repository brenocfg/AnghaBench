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
typedef  size_t u16 ;
struct bnxt_vnic_info {int /*<<< orphan*/  flags; } ;
struct bnxt {int flags; int rx_nr_rings; size_t nr_vnics; int /*<<< orphan*/  dev; struct bnxt_vnic_info* vnic_info; } ;

/* Variables and functions */
 int BNXT_FLAG_CHIP_P5 ; 
 int BNXT_FLAG_NEW_RSS_CAP ; 
 int /*<<< orphan*/  BNXT_VNIC_RFS_FLAG ; 
 int /*<<< orphan*/  BNXT_VNIC_RFS_NEW_RSS_FLAG ; 
 int bnxt_hwrm_vnic_alloc (struct bnxt*,size_t,size_t,int) ; 
 int bnxt_setup_vnic (struct bnxt*,size_t) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,size_t,int) ; 

__attribute__((used)) static int bnxt_alloc_rfs_vnics(struct bnxt *bp)
{
#ifdef CONFIG_RFS_ACCEL
	int i, rc = 0;

	if (bp->flags & BNXT_FLAG_CHIP_P5)
		return 0;

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