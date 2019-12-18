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
 int /*<<< orphan*/  cmos_use_acpi_alarm () ; 
 scalar_t__ is_hpet_enabled () ; 

__attribute__((used)) static inline int use_hpet_alarm(void)
{
	return is_hpet_enabled() && !cmos_use_acpi_alarm();
}