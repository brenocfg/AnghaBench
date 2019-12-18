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
struct mt7601u_dev {TYPE_1__* ee; } ;
struct TYPE_2__ {int rf_freq_off; } ;

/* Variables and functions */
 int BIT (int) ; 
 size_t MT_EE_FREQ_OFFSET ; 
 size_t MT_EE_FREQ_OFFSET_COMPENSATION ; 
 void* field_validate (int) ; 

__attribute__((used)) static void
mt7601u_set_rf_freq_off(struct mt7601u_dev *dev, u8 *eeprom)
{
	u8 comp;

	dev->ee->rf_freq_off = field_validate(eeprom[MT_EE_FREQ_OFFSET]);
	comp = field_validate(eeprom[MT_EE_FREQ_OFFSET_COMPENSATION]);

	if (comp & BIT(7))
		dev->ee->rf_freq_off -= comp & 0x7f;
	else
		dev->ee->rf_freq_off += comp;
}