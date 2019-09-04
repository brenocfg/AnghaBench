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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int i2c_master_send (struct i2c_client*,int*,int) ; 

__attribute__((used)) static int
write_reg( struct i2c_client *cl, int reg, int data, int len )
{
	u8 tmp[3];

	if( len < 1 || len > 2 || data < 0 )
		return -EINVAL;

	tmp[0] = reg;
	tmp[1] = (len == 1) ? data : (data >> 8);
	tmp[2] = data;
	len++;
	
	if( i2c_master_send(cl, tmp, len) != len )
		return -ENODEV;
	return 0;
}