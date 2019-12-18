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
struct w83627ehf_data {int /*<<< orphan*/ * reg_temp_config; int /*<<< orphan*/ * reg_temp_hyst; int /*<<< orphan*/ * reg_temp_over; int /*<<< orphan*/ * reg_temp; int /*<<< orphan*/ * temp_src; } ;

/* Variables and functions */
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void w82627ehf_swap_tempreg(struct w83627ehf_data *data,
				   int r1, int r2)
{
	swap(data->temp_src[r1], data->temp_src[r2]);
	swap(data->reg_temp[r1], data->reg_temp[r2]);
	swap(data->reg_temp_over[r1], data->reg_temp_over[r2]);
	swap(data->reg_temp_hyst[r1], data->reg_temp_hyst[r2]);
	swap(data->reg_temp_config[r1], data->reg_temp_config[r2]);
}