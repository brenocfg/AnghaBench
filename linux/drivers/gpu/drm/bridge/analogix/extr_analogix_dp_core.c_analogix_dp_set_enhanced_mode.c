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
typedef  int /*<<< orphan*/  u8 ;
struct analogix_dp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  analogix_dp_enable_enhanced_mode (struct analogix_dp_device*,int /*<<< orphan*/ ) ; 
 int analogix_dp_enable_rx_to_enhanced_mode (struct analogix_dp_device*,int /*<<< orphan*/ ) ; 
 int analogix_dp_is_enhanced_mode_available (struct analogix_dp_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int analogix_dp_set_enhanced_mode(struct analogix_dp_device *dp)
{
	u8 data;
	int ret;

	ret = analogix_dp_is_enhanced_mode_available(dp, &data);
	if (ret < 0)
		return ret;

	ret = analogix_dp_enable_rx_to_enhanced_mode(dp, data);
	if (ret < 0)
		return ret;

	analogix_dp_enable_enhanced_mode(dp, data);

	return 0;
}