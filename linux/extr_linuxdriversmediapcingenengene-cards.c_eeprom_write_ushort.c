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
typedef  int u8 ;
typedef  int u16 ;
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int WriteEEProm (struct i2c_adapter*,int,int,int*) ; 

__attribute__((used)) static int eeprom_write_ushort(struct i2c_adapter *adapter, u16 tag, u16 data)
{
	int stat;
	u8 buf[2];

	buf[0] = data >> 8;
	buf[1] = data & 0xff;
	stat = WriteEEProm(adapter, tag, 2, buf);
	if (stat)
		return stat;
	return 0;
}