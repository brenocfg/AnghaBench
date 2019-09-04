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
struct cdn_dp_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_GET_SINK_COUNT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DP_SINK_COUNT ; 
 int cdn_dp_dpcd_read (struct cdn_dp_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cdn_dp_get_sink_count(struct cdn_dp_device *dp, u8 *sink_count)
{
	int ret;
	u8 value;

	*sink_count = 0;
	ret = cdn_dp_dpcd_read(dp, DP_SINK_COUNT, &value, 1);
	if (ret)
		return ret;

	*sink_count = DP_GET_SINK_COUNT(value);
	return 0;
}