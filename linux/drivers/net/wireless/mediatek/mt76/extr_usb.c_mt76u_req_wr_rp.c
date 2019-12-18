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
typedef  scalar_t__ u32 ;
struct mt76_usb {int /*<<< orphan*/  usb_ctrl_mtx; } ;
struct mt76_reg_pair {int /*<<< orphan*/  value; scalar_t__ reg; } ;
struct mt76_dev {struct mt76_usb usb; } ;

/* Variables and functions */
 int /*<<< orphan*/  __mt76u_wr (struct mt76_dev*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
mt76u_req_wr_rp(struct mt76_dev *dev, u32 base,
		const struct mt76_reg_pair *data, int len)
{
	struct mt76_usb *usb = &dev->usb;

	mutex_lock(&usb->usb_ctrl_mtx);
	while (len > 0) {
		__mt76u_wr(dev, base + data->reg, data->value);
		len--;
		data++;
	}
	mutex_unlock(&usb->usb_ctrl_mtx);

	return 0;
}