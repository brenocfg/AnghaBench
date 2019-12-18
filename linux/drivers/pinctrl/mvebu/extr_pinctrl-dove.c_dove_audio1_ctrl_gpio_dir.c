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
struct mvebu_mpp_ctrl_data {int dummy; } ;

/* Variables and functions */
 int ENOTSUPP ; 

__attribute__((used)) static int dove_audio1_ctrl_gpio_dir(struct mvebu_mpp_ctrl_data *data,
				     unsigned pid, bool input)
{
	if (pid < 52 || pid > 57)
		return -ENOTSUPP;
	return 0;
}