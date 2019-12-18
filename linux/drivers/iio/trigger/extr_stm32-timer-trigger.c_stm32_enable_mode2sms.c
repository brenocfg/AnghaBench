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

/* Variables and functions */
 int EINVAL ; 

__attribute__((used)) static int stm32_enable_mode2sms(int mode)
{
	switch (mode) {
	case 0:
		return 0;
	case 1:
		return 5;
	case 2:
		return 6;
	}

	return -EINVAL;
}