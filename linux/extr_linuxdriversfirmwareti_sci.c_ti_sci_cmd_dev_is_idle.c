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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct ti_sci_handle {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MSG_DEVICE_SW_STATE_RETENTION ; 
 int ti_sci_get_device_state (struct ti_sci_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ti_sci_cmd_dev_is_idle(const struct ti_sci_handle *handle, u32 id,
				  bool *r_state)
{
	int ret;
	u8 state;

	if (!r_state)
		return -EINVAL;

	ret = ti_sci_get_device_state(handle, id, NULL, NULL, &state, NULL);
	if (ret)
		return ret;

	*r_state = (state == MSG_DEVICE_SW_STATE_RETENTION);

	return 0;
}