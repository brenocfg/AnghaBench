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
typedef  int /*<<< orphan*/  u8 ;
struct dvb_usb_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_MAC_START ; 
 int EEPROM_MAC_TOTAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ technisat_usb2_eeprom_lrc_read (struct dvb_usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int technisat_usb2_read_mac_address(struct dvb_usb_device *d,
		u8 mac[])
{
	u8 buf[EEPROM_MAC_TOTAL];

	if (technisat_usb2_eeprom_lrc_read(d, EEPROM_MAC_START,
				buf, EEPROM_MAC_TOTAL, 4) != 0)
		return -ENODEV;

	memcpy(mac, buf, 6);
	return 0;
}