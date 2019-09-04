#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint ;
struct kovaplus_device {size_t actual_profile; TYPE_1__* profile_settings; int /*<<< orphan*/  actual_y_sensitivity; int /*<<< orphan*/  actual_x_sensitivity; int /*<<< orphan*/  actual_cpi; } ;
struct TYPE_2__ {int /*<<< orphan*/  sensitivity_y; int /*<<< orphan*/  sensitivity_x; int /*<<< orphan*/  cpi_startup_level; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_1__*) ; 

__attribute__((used)) static void kovaplus_profile_activated(struct kovaplus_device *kovaplus,
		uint new_profile_index)
{
	if (new_profile_index >= ARRAY_SIZE(kovaplus->profile_settings))
		return;
	kovaplus->actual_profile = new_profile_index;
	kovaplus->actual_cpi = kovaplus->profile_settings[new_profile_index].cpi_startup_level;
	kovaplus->actual_x_sensitivity = kovaplus->profile_settings[new_profile_index].sensitivity_x;
	kovaplus->actual_y_sensitivity = kovaplus->profile_settings[new_profile_index].sensitivity_y;
}