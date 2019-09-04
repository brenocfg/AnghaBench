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
struct mag3110_data {int ctrl_reg1; } ;

/* Variables and functions */
 int MAG3110_CTRL_DR_SHIFT ; 
 int** mag3110_samp_freq ; 

__attribute__((used)) static int mag3110_calculate_sleep(struct mag3110_data *data)
{
	int ret, i = data->ctrl_reg1 >> MAG3110_CTRL_DR_SHIFT;

	if (mag3110_samp_freq[i][0] > 0)
		ret = 1000 / mag3110_samp_freq[i][0];
	else
		ret = 1000;

	return ret == 0 ? 1 : ret;
}