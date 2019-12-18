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
typedef  int /*<<< orphan*/  u32 ;
struct mt76_reg_pair {int dummy; } ;
struct mt76_dev {TYPE_1__* mcu_ops; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int (* mcu_wr_rp ) (struct mt76_dev*,int /*<<< orphan*/ ,struct mt76_reg_pair const*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MT76_STATE_MCU_RUNNING ; 
 int mt76u_req_wr_rp (struct mt76_dev*,int /*<<< orphan*/ ,struct mt76_reg_pair const*,int) ; 
 int stub1 (struct mt76_dev*,int /*<<< orphan*/ ,struct mt76_reg_pair const*,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mt76u_wr_rp(struct mt76_dev *dev, u32 base,
	    const struct mt76_reg_pair *data, int n)
{
	if (test_bit(MT76_STATE_MCU_RUNNING, &dev->state))
		return dev->mcu_ops->mcu_wr_rp(dev, base, data, n);
	else
		return mt76u_req_wr_rp(dev, base, data, n);
}