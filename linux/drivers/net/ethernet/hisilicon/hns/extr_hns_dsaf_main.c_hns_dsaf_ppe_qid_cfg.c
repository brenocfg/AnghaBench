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
struct dsaf_device {int dummy; } ;

/* Variables and functions */
 int DSAF_COMM_CHN ; 
 scalar_t__ DSAF_PPE_QID_CFG_0_REG ; 
 int /*<<< orphan*/  DSAF_PPE_QID_CFG_M ; 
 int /*<<< orphan*/  DSAF_PPE_QID_CFG_S ; 
 int /*<<< orphan*/  dsaf_set_dev_field (struct dsaf_device*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
hns_dsaf_ppe_qid_cfg(struct dsaf_device *dsaf_dev, u32 qid_cfg)
{
	u32 i;

	for (i = 0; i < DSAF_COMM_CHN; i++) {
		dsaf_set_dev_field(dsaf_dev,
				   DSAF_PPE_QID_CFG_0_REG + 0x0004 * i,
				   DSAF_PPE_QID_CFG_M, DSAF_PPE_QID_CFG_S,
				   qid_cfg);
	}
}