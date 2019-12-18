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
struct TYPE_3__ {scalar_t__* rssi_offset; } ;
struct TYPE_4__ {TYPE_1__ rx; } ;
struct mt76x02_dev {TYPE_2__ cal; } ;
typedef  scalar_t__ s8 ;

/* Variables and functions */
 int /*<<< orphan*/  mt76x02_field_valid (int /*<<< orphan*/ ) ; 
 scalar_t__ mt76x02_sign_extend_optional (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mt76x2_set_rssi_offset(struct mt76x02_dev *dev, int chain, u8 val)
{
	s8 *dest = dev->cal.rx.rssi_offset;

	if (!mt76x02_field_valid(val)) {
		dest[chain] = 0;
		return;
	}

	dest[chain] = mt76x02_sign_extend_optional(val, 7);
}