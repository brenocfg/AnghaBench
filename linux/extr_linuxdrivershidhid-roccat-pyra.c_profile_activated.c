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
struct pyra_device {unsigned int actual_profile; TYPE_1__* profile_settings; int /*<<< orphan*/  actual_cpi; } ;
struct TYPE_2__ {int /*<<< orphan*/  y_cpi; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 

__attribute__((used)) static void profile_activated(struct pyra_device *pyra,
		unsigned int new_profile)
{
	if (new_profile >= ARRAY_SIZE(pyra->profile_settings))
		return;
	pyra->actual_profile = new_profile;
	pyra->actual_cpi = pyra->profile_settings[pyra->actual_profile].y_cpi;
}