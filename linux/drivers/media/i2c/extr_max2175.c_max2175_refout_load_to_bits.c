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
typedef  int u32 ;
struct i2c_client {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int max2175_refout_load_to_bits(struct i2c_client *client, u32 load,
				       u32 *bits)
{
	if (load <= 40)
		*bits = load / 10;
	else if (load >= 60 && load <= 70)
		*bits = load / 10 - 1;
	else
		return -EINVAL;

	return 0;
}