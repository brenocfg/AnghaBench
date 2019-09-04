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
typedef  int /*<<< orphan*/  u32 ;
struct ti_sci_handle {int dummy; } ;

/* Variables and functions */
 int ti_sci_get_device_state (struct ti_sci_handle const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ti_sci_cmd_dev_is_valid(const struct ti_sci_handle *handle, u32 id)
{
	u8 unused;

	/* check the device state which will also tell us if the ID is valid */
	return ti_sci_get_device_state(handle, id, NULL, NULL, NULL, &unused);
}