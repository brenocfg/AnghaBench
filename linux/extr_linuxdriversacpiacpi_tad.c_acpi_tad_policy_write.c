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
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;

/* Variables and functions */
 int acpi_tad_wake_write (struct device*,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  policy_specval ; 

__attribute__((used)) static int acpi_tad_policy_write(struct device *dev, const char *buf,
				 u32 timer_id)
{
	return acpi_tad_wake_write(dev, buf, "_STP", timer_id, policy_specval);
}