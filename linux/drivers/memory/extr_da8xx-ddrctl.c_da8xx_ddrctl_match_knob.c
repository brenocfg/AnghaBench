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
struct da8xx_ddrctl_setting {int /*<<< orphan*/  name; } ;
struct da8xx_ddrctl_config_knob {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct da8xx_ddrctl_config_knob*) ; 
 struct da8xx_ddrctl_config_knob* da8xx_ddrctl_knobs ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct da8xx_ddrctl_config_knob *
da8xx_ddrctl_match_knob(const struct da8xx_ddrctl_setting *setting)
{
	const struct da8xx_ddrctl_config_knob *knob;
	int i;

	for (i = 0; i < ARRAY_SIZE(da8xx_ddrctl_knobs); i++) {
		knob = &da8xx_ddrctl_knobs[i];

		if (strcmp(knob->name, setting->name) == 0)
			return knob;
	}

	return NULL;
}