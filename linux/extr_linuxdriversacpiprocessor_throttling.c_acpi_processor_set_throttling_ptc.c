#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_3__ {int state_count; int state; } ;
struct TYPE_4__ {int /*<<< orphan*/  throttling; } ;
struct acpi_processor {int throttling_platform_limit; TYPE_1__ throttling; TYPE_2__ flags; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int EPERM ; 
 int acpi_get_throttling_value (struct acpi_processor*,int,scalar_t__*) ; 
 int /*<<< orphan*/  acpi_write_throttling_state (struct acpi_processor*,scalar_t__) ; 

__attribute__((used)) static int acpi_processor_set_throttling_ptc(struct acpi_processor *pr,
					     int state, bool force)
{
	int ret;
	u64 value;

	if (!pr)
		return -EINVAL;

	if ((state < 0) || (state > (pr->throttling.state_count - 1)))
		return -EINVAL;

	if (!pr->flags.throttling)
		return -ENODEV;

	if (!force && (state == pr->throttling.state))
		return 0;

	if (state < pr->throttling_platform_limit)
		return -EPERM;

	value = 0;
	ret = acpi_get_throttling_value(pr, state, &value);
	if (ret >= 0) {
		acpi_write_throttling_state(pr, value);
		pr->throttling.state = state;
	}

	return 0;
}