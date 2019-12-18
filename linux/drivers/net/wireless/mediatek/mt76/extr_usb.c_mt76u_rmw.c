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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  usb_ctrl_mtx; } ;
struct mt76_dev {TYPE_1__ usb; } ;

/* Variables and functions */
 int __mt76u_rr (struct mt76_dev*,int) ; 
 int /*<<< orphan*/  __mt76u_wr (struct mt76_dev*,int,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static u32 mt76u_rmw(struct mt76_dev *dev, u32 addr,
		     u32 mask, u32 val)
{
	mutex_lock(&dev->usb.usb_ctrl_mtx);
	val |= __mt76u_rr(dev, addr) & ~mask;
	__mt76u_wr(dev, addr, val);
	mutex_unlock(&dev->usb.usb_ctrl_mtx);

	return val;
}