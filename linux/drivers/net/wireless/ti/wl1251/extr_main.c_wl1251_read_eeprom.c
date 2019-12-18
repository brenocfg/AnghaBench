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
struct wl1251 {int dummy; } ;
typedef  scalar_t__ off_t ;

/* Variables and functions */
 int /*<<< orphan*/  EE_START ; 
 int wl1251_read_eeprom_byte (struct wl1251*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl1251_reg_write32 (struct wl1251*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wl1251_read_eeprom(struct wl1251 *wl, off_t offset,
			      u8 *data, size_t len)
{
	size_t i;
	int ret;

	wl1251_reg_write32(wl, EE_START, 0);

	for (i = 0; i < len; i++) {
		ret = wl1251_read_eeprom_byte(wl, offset + i, &data[i]);
		if (ret < 0)
			return ret;
	}

	return 0;
}