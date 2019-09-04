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
struct gp2ap020a00f_data {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  GP2AP020A00F_FLAG_LUX_MODE_HI ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gp2ap020a00f_output_to_lux(struct gp2ap020a00f_data *data,
						int *output_val)
{
	if (test_bit(GP2AP020A00F_FLAG_LUX_MODE_HI, &data->flags))
		*output_val *= 16;
}