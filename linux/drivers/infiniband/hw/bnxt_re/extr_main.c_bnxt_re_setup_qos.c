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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_2__ {int prio; } ;
struct bnxt_re_dev {scalar_t__ cur_prio_map; TYPE_1__ qplib_res; int /*<<< orphan*/ * cosq; } ;

/* Variables and functions */
 int bnxt_qplib_map_tc2cos (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ bnxt_re_get_priority_mask (struct bnxt_re_dev*) ; 
 int /*<<< orphan*/  bnxt_re_parse_cid_map (scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int bnxt_re_query_hwrm_pri2cos (struct bnxt_re_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bnxt_re_update_gid (struct bnxt_re_dev*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  rdev_to_dev (struct bnxt_re_dev*) ; 

__attribute__((used)) static int bnxt_re_setup_qos(struct bnxt_re_dev *rdev)
{
	u8 prio_map = 0;
	u64 cid_map;
	int rc;

	/* Get priority for roce */
	prio_map = bnxt_re_get_priority_mask(rdev);

	if (prio_map == rdev->cur_prio_map)
		return 0;
	rdev->cur_prio_map = prio_map;
	/* Get cosq id for this priority */
	rc = bnxt_re_query_hwrm_pri2cos(rdev, 0, &cid_map);
	if (rc) {
		dev_warn(rdev_to_dev(rdev), "no cos for p_mask %x\n", prio_map);
		return rc;
	}
	/* Parse CoS IDs for app priority */
	bnxt_re_parse_cid_map(prio_map, (u8 *)&cid_map, rdev->cosq);

	/* Config BONO. */
	rc = bnxt_qplib_map_tc2cos(&rdev->qplib_res, rdev->cosq);
	if (rc) {
		dev_warn(rdev_to_dev(rdev), "no tc for cos{%x, %x}\n",
			 rdev->cosq[0], rdev->cosq[1]);
		return rc;
	}

	/* Actual priorities are not programmed as they are already
	 * done by L2 driver; just enable or disable priority vlan tagging
	 */
	if ((prio_map == 0 && rdev->qplib_res.prio) ||
	    (prio_map != 0 && !rdev->qplib_res.prio)) {
		rdev->qplib_res.prio = prio_map ? true : false;

		bnxt_re_update_gid(rdev);
	}

	return 0;
}