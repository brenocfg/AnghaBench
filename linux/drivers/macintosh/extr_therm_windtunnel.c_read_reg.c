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
typedef  unsigned int u8 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int i2c_master_recv (struct i2c_client*,unsigned int*,int) ; 
 int i2c_master_send (struct i2c_client*,unsigned int*,int) ; 

__attribute__((used)) static int
read_reg( struct i2c_client *cl, int reg, int len )
{
	u8 buf[2];

	if( len != 1 && len != 2 )
		return -EINVAL;
	buf[0] = reg;
	if( i2c_master_send(cl, buf, 1) != 1 )
		return -ENODEV;
	if( i2c_master_recv(cl, buf, len) != len )
		return -ENODEV;
	return (len == 2)? ((unsigned int)buf[0] << 8) | buf[1] : buf[0];
}