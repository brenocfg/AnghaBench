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
struct i2c_client {int /*<<< orphan*/  addr; } ;
struct TYPE_2__ {struct i2c_client* fan; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ) ; 
 int read_reg (struct i2c_client*,int,int) ; 
 TYPE_1__ x ; 

__attribute__((used)) static int
attach_fan( struct i2c_client *cl )
{
	if( x.fan )
		goto out;

	/* check that this is an ADM1030 */
	if( read_reg(cl, 0x3d, 1) != 0x30 || read_reg(cl, 0x3e, 1) != 0x41 )
		goto out;
	printk("ADM1030 fan controller [@%02x]\n", cl->addr );

	x.fan = cl;
 out:
	return 0;
}