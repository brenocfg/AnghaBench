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
struct dsaf_device {int /*<<< orphan*/  dsaf_ver; } ;

/* Variables and functions */
 scalar_t__ AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSAF_FC_XGE_TX_PAUSE_S ; 
 int /*<<< orphan*/  DSAF_XGE_CTRL_SIG_CFG_0_REG ; 
 int /*<<< orphan*/  dsaf_set_dev_bit (struct dsaf_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hns_dsaf_rocee_bp_en(struct dsaf_device *dsaf_dev)
{
	if (AE_IS_VER1(dsaf_dev->dsaf_ver))
		dsaf_set_dev_bit(dsaf_dev, DSAF_XGE_CTRL_SIG_CFG_0_REG,
				 DSAF_FC_XGE_TX_PAUSE_S, 1);
}