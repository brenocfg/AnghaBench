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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_2__ {int rt; } ;
struct rt2x00_dev {TYPE_1__ chip; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_BBP_REG_ID ; 
 unsigned int EEPROM_BBP_SIZE ; 
 int /*<<< orphan*/  EEPROM_BBP_START ; 
 int /*<<< orphan*/  EEPROM_BBP_VALUE ; 
#define  RT2860 144 
#define  RT2872 143 
#define  RT2883 142 
#define  RT3070 141 
#define  RT3071 140 
#define  RT3090 139 
#define  RT3290 138 
#define  RT3352 137 
#define  RT3390 136 
#define  RT3572 135 
#define  RT3593 134 
#define  RT3883 133 
#define  RT5350 132 
#define  RT5390 131 
#define  RT5392 130 
#define  RT5592 129 
#define  RT6352 128 
 int /*<<< orphan*/  rt2800_bbp_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rt2800_eeprom_read_from_array (struct rt2x00_dev*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  rt2800_init_bbp_28xx (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_bbp_305x_soc (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_bbp_30xx (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_bbp_3290 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_bbp_3352 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_bbp_3390 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_bbp_3572 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_bbp_3593 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_bbp_3883 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_bbp_53xx (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_bbp_5592 (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2800_init_bbp_6352 (struct rt2x00_dev*) ; 
 scalar_t__ rt2800_is_305x_soc (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_get_field16 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2800_init_bbp(struct rt2x00_dev *rt2x00dev)
{
	unsigned int i;
	u16 eeprom;
	u8 reg_id;
	u8 value;

	if (rt2800_is_305x_soc(rt2x00dev))
		rt2800_init_bbp_305x_soc(rt2x00dev);

	switch (rt2x00dev->chip.rt) {
	case RT2860:
	case RT2872:
	case RT2883:
		rt2800_init_bbp_28xx(rt2x00dev);
		break;
	case RT3070:
	case RT3071:
	case RT3090:
		rt2800_init_bbp_30xx(rt2x00dev);
		break;
	case RT3290:
		rt2800_init_bbp_3290(rt2x00dev);
		break;
	case RT3352:
	case RT5350:
		rt2800_init_bbp_3352(rt2x00dev);
		break;
	case RT3390:
		rt2800_init_bbp_3390(rt2x00dev);
		break;
	case RT3572:
		rt2800_init_bbp_3572(rt2x00dev);
		break;
	case RT3593:
		rt2800_init_bbp_3593(rt2x00dev);
		return;
	case RT3883:
		rt2800_init_bbp_3883(rt2x00dev);
		return;
	case RT5390:
	case RT5392:
		rt2800_init_bbp_53xx(rt2x00dev);
		break;
	case RT5592:
		rt2800_init_bbp_5592(rt2x00dev);
		return;
	case RT6352:
		rt2800_init_bbp_6352(rt2x00dev);
		break;
	}

	for (i = 0; i < EEPROM_BBP_SIZE; i++) {
		eeprom = rt2800_eeprom_read_from_array(rt2x00dev,
						       EEPROM_BBP_START, i);

		if (eeprom != 0xffff && eeprom != 0x0000) {
			reg_id = rt2x00_get_field16(eeprom, EEPROM_BBP_REG_ID);
			value = rt2x00_get_field16(eeprom, EEPROM_BBP_VALUE);
			rt2800_bbp_write(rt2x00dev, reg_id, value);
		}
	}
}