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
typedef  int u8 ;
struct mt76x02_rx_freq_cal {int freq_offset; } ;
struct TYPE_2__ {struct mt76x02_rx_freq_cal rx; } ;
struct mt76x02_dev {TYPE_1__ cal; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_EE_FREQ_OFFSET ; 
 int /*<<< orphan*/  MT_EE_TSSI_BOUND4 ; 
 int mt76x02_eeprom_get (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_field_valid (int) ; 
 int mt76x02_sign_extend (int,int) ; 

__attribute__((used)) static void mt76x0_set_freq_offset(struct mt76x02_dev *dev)
{
	struct mt76x02_rx_freq_cal *caldata = &dev->cal.rx;
	u8 val;

	val = mt76x02_eeprom_get(dev, MT_EE_FREQ_OFFSET);
	if (!mt76x02_field_valid(val))
		val = 0;
	caldata->freq_offset = val;

	val = mt76x02_eeprom_get(dev, MT_EE_TSSI_BOUND4) >> 8;
	if (!mt76x02_field_valid(val))
		val = 0;

	caldata->freq_offset -= mt76x02_sign_extend(val, 8);
}