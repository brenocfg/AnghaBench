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

__attribute__((used)) static int stm32_sms2enable_mode(int mode)
{
	switch (mode) {
	case 0:
		return 0;
	case 5:
		return 1;
	case 6:
		return 2;
	}

	return -EINVAL;
}