#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int rp_len; scalar_t__ base; TYPE_1__* rp; scalar_t__ burst; } ;
struct mt76_usb {TYPE_2__ mcu; } ;
struct mt76_dev {struct mt76_usb usb; } ;
struct TYPE_3__ {scalar_t__ reg; scalar_t__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ get_unaligned_le32 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mt76x02u_multiple_mcu_reads(struct mt76_dev *dev, u8 *data, int len)
{
	struct mt76_usb *usb = &dev->usb;
	u32 reg, val;
	int i;

	if (usb->mcu.burst) {
		WARN_ON_ONCE(len / 4 != usb->mcu.rp_len);

		reg = usb->mcu.rp[0].reg - usb->mcu.base;
		for (i = 0; i < usb->mcu.rp_len; i++) {
			val = get_unaligned_le32(data + 4 * i);
			usb->mcu.rp[i].reg = reg++;
			usb->mcu.rp[i].value = val;
		}
	} else {
		WARN_ON_ONCE(len / 8 != usb->mcu.rp_len);

		for (i = 0; i < usb->mcu.rp_len; i++) {
			reg = get_unaligned_le32(data + 8 * i) -
			      usb->mcu.base;
			val = get_unaligned_le32(data + 8 * i + 4);

			WARN_ON_ONCE(usb->mcu.rp[i].reg != reg);
			usb->mcu.rp[i].value = val;
		}
	}
}