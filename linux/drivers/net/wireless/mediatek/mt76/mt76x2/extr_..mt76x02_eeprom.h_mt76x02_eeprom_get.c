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
struct TYPE_3__ {scalar_t__ data; } ;
struct TYPE_4__ {TYPE_1__ eeprom; } ;
struct mt76x02_dev {TYPE_2__ mt76; } ;
typedef  enum mt76x02_eeprom_field { ____Placeholder_mt76x02_eeprom_field } mt76x02_eeprom_field ;

/* Variables and functions */
 int __MT_EE_MAX ; 
 int get_unaligned_le16 (scalar_t__) ; 

__attribute__((used)) static inline int
mt76x02_eeprom_get(struct mt76x02_dev *dev,
		   enum mt76x02_eeprom_field field)
{
	if ((field & 1) || field >= __MT_EE_MAX)
		return -1;

	return get_unaligned_le16(dev->mt76.eeprom.data + field);
}