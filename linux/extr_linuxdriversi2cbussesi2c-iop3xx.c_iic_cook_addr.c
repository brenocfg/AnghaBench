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
struct i2c_msg {int dummy; } ;

/* Variables and functions */
 unsigned char i2c_8bit_addr_from_msg (struct i2c_msg*) ; 

__attribute__((used)) static inline unsigned char
iic_cook_addr(struct i2c_msg *msg)
{
	unsigned char addr;

	addr = i2c_8bit_addr_from_msg(msg);

	return addr;
}