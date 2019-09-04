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
typedef  int /*<<< orphan*/  u16 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 unsigned int cx25840_read (struct i2c_client*,int /*<<< orphan*/ ) ; 
 int cx25840_write (struct i2c_client*,int /*<<< orphan*/ ,unsigned int) ; 

int cx25840_and_or(struct i2c_client *client, u16 addr, unsigned and_mask,
		   u8 or_value)
{
	return cx25840_write(client, addr,
			     (cx25840_read(client, addr) & and_mask) |
			     or_value);
}