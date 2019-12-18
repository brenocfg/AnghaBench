#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  int u16 ;
struct TYPE_5__ {scalar_t__* data; } ;
struct TYPE_4__ {scalar_t__* data; } ;
struct TYPE_6__ {TYPE_2__ otp; TYPE_1__ eeprom; } ;
struct mt7615_dev {TYPE_3__ mt76; } ;

/* Variables and functions */
 int ARRAY_SIZE (int const*) ; 

__attribute__((used)) static void mt7615_apply_cal_free_data(struct mt7615_dev *dev)
{
	static const u16 ical[] = {
		0x53, 0x54, 0x55, 0x56, 0x57, 0x5c, 0x5d, 0x62, 0x63, 0x68,
		0x69, 0x6e, 0x6f, 0x73, 0x74, 0x78, 0x79, 0x82, 0x83, 0x87,
		0x88, 0x8c, 0x8d, 0x91, 0x92, 0x96, 0x97, 0x9b, 0x9c, 0xa0,
		0xa1, 0xaa, 0xab, 0xaf, 0xb0, 0xb4, 0xb5, 0xb9, 0xba, 0xf4,
		0xf7, 0xff,
		0x140, 0x141, 0x145, 0x146, 0x14a, 0x14b, 0x154, 0x155, 0x159,
		0x15a, 0x15e, 0x15f, 0x163, 0x164, 0x168, 0x169, 0x16d, 0x16e,
		0x172, 0x173, 0x17c, 0x17d, 0x181, 0x182, 0x186, 0x187, 0x18b,
		0x18c
	};
	static const u16 ical_nocheck[] = {
		0x110, 0x111, 0x112, 0x113, 0x114, 0x115, 0x116, 0x117, 0x118,
		0x1b5, 0x1b6, 0x1b7, 0x3ac, 0x3ad, 0x3ae, 0x3af, 0x3b0, 0x3b1,
		0x3b2
	};
	u8 *eeprom = dev->mt76.eeprom.data;
	u8 *otp = dev->mt76.otp.data;
	int i;

	if (!otp)
		return;

	for (i = 0; i < ARRAY_SIZE(ical); i++)
		if (!otp[ical[i]])
			return;

	for (i = 0; i < ARRAY_SIZE(ical); i++)
		eeprom[ical[i]] = otp[ical[i]];

	for (i = 0; i < ARRAY_SIZE(ical_nocheck); i++)
		eeprom[ical_nocheck[i]] = otp[ical_nocheck[i]];
}