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
struct mt76_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MCU_CMD_RESTART_DL_REQ ; 
 int __mt76_mcu_send_msg (struct mt76_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt7615_mcu_restart(struct mt76_dev *dev)
{
	return __mt76_mcu_send_msg(dev, -MCU_CMD_RESTART_DL_REQ, NULL,
				   0, true);
}