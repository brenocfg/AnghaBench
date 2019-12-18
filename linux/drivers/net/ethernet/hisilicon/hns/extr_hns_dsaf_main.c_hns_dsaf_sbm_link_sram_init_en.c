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
struct dsaf_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSAF_CFG_0_REG ; 
 int /*<<< orphan*/  DSAF_CFG_SBM_INIT_S ; 
 int /*<<< orphan*/  dsaf_set_dev_bit (struct dsaf_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void hns_dsaf_sbm_link_sram_init_en(struct dsaf_device *dsaf_dev)
{
	dsaf_set_dev_bit(dsaf_dev, DSAF_CFG_0_REG, DSAF_CFG_SBM_INIT_S, 1);
}