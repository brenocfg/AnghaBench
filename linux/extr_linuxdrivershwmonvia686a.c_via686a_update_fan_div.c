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
struct via686a_data {int* fan_div; } ;

/* Variables and functions */
 int /*<<< orphan*/  VIA686A_REG_FANDIV ; 
 int via686a_read_value (struct via686a_data*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void via686a_update_fan_div(struct via686a_data *data)
{
	int reg = via686a_read_value(data, VIA686A_REG_FANDIV);
	data->fan_div[0] = (reg >> 4) & 0x03;
	data->fan_div[1] = reg >> 6;
}