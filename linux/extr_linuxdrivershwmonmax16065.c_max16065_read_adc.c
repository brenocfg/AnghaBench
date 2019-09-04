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
 int i2c_smbus_read_word_swapped (struct i2c_client*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int max16065_read_adc(struct i2c_client *client, int reg)
{
	int rv;

	rv = i2c_smbus_read_word_swapped(client, reg);
	if (unlikely(rv < 0))
		return rv;
	return rv >> 6;
}