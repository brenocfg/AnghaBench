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
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx25840_write (struct i2c_client*,int,int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void init_dll1(struct i2c_client *client)
{
	/* This is the Hauppauge sequence used to
	 * initialize the Delay Lock Loop 1 (ADC DLL). */
	cx25840_write(client, 0x159, 0x23);
	cx25840_write(client, 0x15a, 0x87);
	cx25840_write(client, 0x15b, 0x06);
	udelay(10);
	cx25840_write(client, 0x159, 0xe1);
	udelay(10);
	cx25840_write(client, 0x15a, 0x86);
	cx25840_write(client, 0x159, 0xe0);
	cx25840_write(client, 0x159, 0xe1);
	cx25840_write(client, 0x15b, 0x10);
}