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
typedef  int /*<<< orphan*/  u32 ;
struct dsaf_device {int /*<<< orphan*/  dsaf_ver; } ;

/* Variables and functions */
 scalar_t__ AE_IS_VER1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DSAF_CFG_0_REG ; 
 int /*<<< orphan*/  DSAF_CFG_MIX_MODE_S ; 
 int /*<<< orphan*/  HNS_DSAF_IS_DEBUG (struct dsaf_device*) ; 
 int /*<<< orphan*/  dsaf_set_dev_bit (struct dsaf_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void hns_dsaf_set_promisc_mode(struct dsaf_device *dsaf_dev, u32 en)
{
	if (AE_IS_VER1(dsaf_dev->dsaf_ver) && !HNS_DSAF_IS_DEBUG(dsaf_dev))
		dsaf_set_dev_bit(dsaf_dev, DSAF_CFG_0_REG,
				 DSAF_CFG_MIX_MODE_S, !!en);
}