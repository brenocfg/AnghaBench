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
struct i2c_adapter {int dummy; } ;

/* Variables and functions */
 int NGENE_XO2_TYPE_CI ; 
 int NGENE_XO2_TYPE_DUOFLEX ; 
 int NGENE_XO2_TYPE_NONE ; 
 scalar_t__ i2c_io (struct i2c_adapter*,int,int*,int,int*,int) ; 

__attribute__((used)) static int port_has_xo2(struct i2c_adapter *i2c, u8 *type, u8 *id)
{
	u8 probe[1] = { 0x00 }, data[4];
	u8 addr = 0x10;

	*type = NGENE_XO2_TYPE_NONE;

	if (i2c_io(i2c, addr, probe, 1, data, 4))
		return 0;
	if (data[0] == 'D' && data[1] == 'F') {
		*id = data[2];
		*type = NGENE_XO2_TYPE_DUOFLEX;
		return 1;
	}
	if (data[0] == 'C' && data[1] == 'I') {
		*id = data[2];
		*type = NGENE_XO2_TYPE_CI;
		return 1;
	}
	return 0;
}