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
typedef  int u32 ;
typedef  int u16 ;
struct dsaf_device {int /*<<< orphan*/  dsaf_mode; int /*<<< orphan*/  dsaf_ver; } ;

/* Variables and functions */
 scalar_t__ AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 scalar_t__ DSAFV2_SERDES_LBK_0_REG ; 
 int /*<<< orphan*/  DSAFV2_SERDES_LBK_QID_M ; 
 int /*<<< orphan*/  DSAFV2_SERDES_LBK_QID_S ; 
 int DSAF_SERVICE_NW_NUM ; 
 int /*<<< orphan*/  dsaf_set_dev_field (struct dsaf_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hns_rcb_get_queue_mode (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void hns_dsaf_inner_qid_cfg(struct dsaf_device *dsaf_dev)
{
	u16 max_q_per_vf, max_vfn;
	u32 q_id, q_num_per_port;
	u32 mac_id;

	if (AE_IS_VER1(dsaf_dev->dsaf_ver))
		return;

	hns_rcb_get_queue_mode(dsaf_dev->dsaf_mode, &max_vfn, &max_q_per_vf);
	q_num_per_port = max_vfn * max_q_per_vf;

	for (mac_id = 0, q_id = 0; mac_id < DSAF_SERVICE_NW_NUM; mac_id++) {
		dsaf_set_dev_field(dsaf_dev,
				   DSAFV2_SERDES_LBK_0_REG + 4 * mac_id,
				   DSAFV2_SERDES_LBK_QID_M,
				   DSAFV2_SERDES_LBK_QID_S,
				   q_id);
		q_id += q_num_per_port;
	}
}