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
typedef  int u8 ;
struct TYPE_3__ {int temp_offset; } ;
struct TYPE_4__ {TYPE_1__ rx; } ;
struct mt76x02_dev {TYPE_2__ cal; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_EE_2G_TARGET_POWER ; 
 int mt76x02_eeprom_get (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 scalar_t__ mt76x02_field_valid (int) ; 
 int mt76x02_sign_extend (int,int) ; 

__attribute__((used)) static void mt76x0_set_temp_offset(struct mt76x02_dev *dev)
{
	u8 val;

	val = mt76x02_eeprom_get(dev, MT_EE_2G_TARGET_POWER) >> 8;
	if (mt76x02_field_valid(val))
		dev->cal.rx.temp_offset = mt76x02_sign_extend(val, 8);
	else
		dev->cal.rx.temp_offset = -10;
}