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
struct dsaf_device {int /*<<< orphan*/  dsaf_mode; } ;

/* Variables and functions */
 scalar_t__ DSAF_MIX_DEF_QID_0_REG ; 
 int DSAF_SERVICE_NW_NUM ; 
 int /*<<< orphan*/  dsaf_set_dev_field (struct dsaf_device*,scalar_t__,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  hns_rcb_get_queue_mode (int /*<<< orphan*/ ,int*,int*) ; 

__attribute__((used)) static void hns_dsaf_mix_def_qid_cfg(struct dsaf_device *dsaf_dev)
{
	u16 max_q_per_vf, max_vfn;
	u32 q_id, q_num_per_port;
	u32 i;

	hns_rcb_get_queue_mode(dsaf_dev->dsaf_mode, &max_vfn, &max_q_per_vf);
	q_num_per_port = max_vfn * max_q_per_vf;

	for (i = 0, q_id = 0; i < DSAF_SERVICE_NW_NUM; i++) {
		dsaf_set_dev_field(dsaf_dev,
				   DSAF_MIX_DEF_QID_0_REG + 0x0004 * i,
				   0xff, 0, q_id);
		q_id += q_num_per_port;
	}
}