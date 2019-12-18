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
struct rt2x00_dev {int dummy; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  MAC_STATUS_CFG ; 
 int /*<<< orphan*/  MAC_STATUS_CFG_BBP_RF_BUSY ; 
 unsigned int REGISTER_BUSY_COUNT ; 
 int /*<<< orphan*/  REGISTER_BUSY_DELAY ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_err (struct rt2x00_dev*,char*) ; 
 int /*<<< orphan*/  rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rt2800_wait_bbp_rf_ready(struct rt2x00_dev *rt2x00dev)
{
	unsigned int i;
	u32 reg;

	for (i = 0; i < REGISTER_BUSY_COUNT; i++) {
		reg = rt2800_register_read(rt2x00dev, MAC_STATUS_CFG);
		if (!rt2x00_get_field32(reg, MAC_STATUS_CFG_BBP_RF_BUSY))
			return 0;

		udelay(REGISTER_BUSY_DELAY);
	}

	rt2x00_err(rt2x00dev, "BBP/RF register access failed, aborting\n");
	return -EACCES;
}