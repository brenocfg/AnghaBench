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
typedef  int /*<<< orphan*/  u16 ;
struct rt2x00_dev {int dummy; } ;
struct link_qual {int /*<<< orphan*/  vgc_level; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_BBPTUNE_R24 ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_R24_LOW ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_R25 ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_R25_LOW ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_R61 ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_R61_LOW ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_VGC ; 
 int /*<<< orphan*/  EEPROM_BBPTUNE_VGCUPPER ; 
 int /*<<< orphan*/  rt2500usb_bbp_write (struct rt2x00_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_eeprom_read (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_get_field16 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2500usb_reset_tuner(struct rt2x00_dev *rt2x00dev,
				  struct link_qual *qual)
{
	u16 eeprom;
	u16 value;

	eeprom = rt2x00_eeprom_read(rt2x00dev, EEPROM_BBPTUNE_R24);
	value = rt2x00_get_field16(eeprom, EEPROM_BBPTUNE_R24_LOW);
	rt2500usb_bbp_write(rt2x00dev, 24, value);

	eeprom = rt2x00_eeprom_read(rt2x00dev, EEPROM_BBPTUNE_R25);
	value = rt2x00_get_field16(eeprom, EEPROM_BBPTUNE_R25_LOW);
	rt2500usb_bbp_write(rt2x00dev, 25, value);

	eeprom = rt2x00_eeprom_read(rt2x00dev, EEPROM_BBPTUNE_R61);
	value = rt2x00_get_field16(eeprom, EEPROM_BBPTUNE_R61_LOW);
	rt2500usb_bbp_write(rt2x00dev, 61, value);

	eeprom = rt2x00_eeprom_read(rt2x00dev, EEPROM_BBPTUNE_VGC);
	value = rt2x00_get_field16(eeprom, EEPROM_BBPTUNE_VGCUPPER);
	rt2500usb_bbp_write(rt2x00dev, 17, value);

	qual->vgc_level = value;
}