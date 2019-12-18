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
struct sc27xx_fgu_data {int /*<<< orphan*/  cur_1000ma_adc; } ;

/* Variables and functions */
 int DIV_ROUND_CLOSEST (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sc27xx_fgu_adc_to_current(struct sc27xx_fgu_data *data, int adc)
{
	return DIV_ROUND_CLOSEST(adc * 1000, data->cur_1000ma_adc);
}