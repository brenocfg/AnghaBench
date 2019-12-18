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
 int /*<<< orphan*/  dove_audio1_ctrl_get (struct mvebu_mpp_ctrl_data*,unsigned int,unsigned long*) ; 

__attribute__((used)) static int dove_audio1_ctrl_gpio_req(struct mvebu_mpp_ctrl_data *data,
				     unsigned pid)
{
	unsigned long config;

	dove_audio1_ctrl_get(data, pid, &config);

	switch (config) {
	case 0x02: /* i2s1 : gpio[56:57] */
	case 0x0e: /* ssp  : gpio[56:57] */
		if (pid >= 56)
			return 0;
		return -ENOTSUPP;
	case 0x08: /* spdifo : gpio[52:55] */
	case 0x0b: /* twsi   : gpio[52:55] */
		if (pid <= 55)
			return 0;
		return -ENOTSUPP;
	case 0x0a: /* all gpio */
		return 0;
	/* 0x00 : i2s1/spdifo : no gpio */
	/* 0x0c : ssp/spdifo  : no gpio */
	/* 0x0f : ssp/twsi    : no gpio */
	}
	return -ENOTSUPP;
}