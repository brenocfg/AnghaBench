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
struct analogix_dp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  analogix_dp_config_interrupt (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  analogix_dp_enable_sw_function (struct analogix_dp_device*) ; 
 int analogix_dp_init_analog_func (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  analogix_dp_init_analog_param (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  analogix_dp_init_aux (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  analogix_dp_init_hpd (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  analogix_dp_init_interrupt (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  analogix_dp_reset (struct analogix_dp_device*) ; 
 int /*<<< orphan*/  analogix_dp_swreset (struct analogix_dp_device*) ; 

__attribute__((used)) static int analogix_dp_init_dp(struct analogix_dp_device *dp)
{
	int ret;

	analogix_dp_reset(dp);

	analogix_dp_swreset(dp);

	analogix_dp_init_analog_param(dp);
	analogix_dp_init_interrupt(dp);

	/* SW defined function Normal operation */
	analogix_dp_enable_sw_function(dp);

	analogix_dp_config_interrupt(dp);
	ret = analogix_dp_init_analog_func(dp);
	if (ret)
		return ret;

	analogix_dp_init_hpd(dp);
	analogix_dp_init_aux(dp);
	return 0;
}