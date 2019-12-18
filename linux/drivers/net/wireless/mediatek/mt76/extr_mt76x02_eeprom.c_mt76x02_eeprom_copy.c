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
struct TYPE_3__ {int size; int data; } ;
struct TYPE_4__ {TYPE_1__ eeprom; } ;
struct mt76x02_dev {TYPE_2__ mt76; } ;
typedef  enum mt76x02_eeprom_field { ____Placeholder_mt76x02_eeprom_field } mt76x02_eeprom_field ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (void*,int,int) ; 

int mt76x02_eeprom_copy(struct mt76x02_dev *dev,
			enum mt76x02_eeprom_field field,
			void *dest, int len)
{
	if (field + len > dev->mt76.eeprom.size)
		return -1;

	memcpy(dest, dev->mt76.eeprom.data + field, len);
	return 0;
}