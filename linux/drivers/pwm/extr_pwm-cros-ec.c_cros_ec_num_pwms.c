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
typedef  scalar_t__ u32 ;
struct cros_ec_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ EC_RES_INVALID_COMMAND ; 
 scalar_t__ EC_RES_INVALID_PARAM ; 
 int ENODEV ; 
 int EPROTO ; 
 int U8_MAX ; 
 int __cros_ec_pwm_get_duty (struct cros_ec_device*,int,scalar_t__*) ; 

__attribute__((used)) static int cros_ec_num_pwms(struct cros_ec_device *ec)
{
	int i, ret;

	/* The index field is only 8 bits */
	for (i = 0; i <= U8_MAX; i++) {
		u32 result = 0;

		ret = __cros_ec_pwm_get_duty(ec, i, &result);
		/* We want to parse EC protocol errors */
		if (ret < 0 && !(ret == -EPROTO && result))
			return ret;

		/*
		 * We look for SUCCESS, INVALID_COMMAND, or INVALID_PARAM
		 * responses; everything else is treated as an error.
		 */
		if (result == EC_RES_INVALID_COMMAND)
			return -ENODEV;
		else if (result == EC_RES_INVALID_PARAM)
			return i;
		else if (result)
			return -EPROTO;
	}

	return U8_MAX;
}