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
struct w83792d_data {int* in; int low_bits; } ;

/* Variables and functions */

__attribute__((used)) static inline long in_count_from_reg(int nr, struct w83792d_data *data)
{
	/* in7 and in8 do not have low bits, but the formula still works */
	return (data->in[nr] << 2) | ((data->low_bits >> (2 * nr)) & 0x03);
}