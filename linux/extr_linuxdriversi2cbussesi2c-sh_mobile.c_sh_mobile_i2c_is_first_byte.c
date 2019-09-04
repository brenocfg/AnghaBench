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
struct sh_mobile_i2c_data {int pos; } ;

/* Variables and functions */

__attribute__((used)) static bool sh_mobile_i2c_is_first_byte(struct sh_mobile_i2c_data *pd)
{
	return pd->pos == -1;
}