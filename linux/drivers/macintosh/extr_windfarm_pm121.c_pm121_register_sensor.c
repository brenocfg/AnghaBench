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
struct wf_sensor {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ wf_get_sensor (struct wf_sensor*) ; 

__attribute__((used)) static struct wf_sensor* pm121_register_sensor(struct wf_sensor *sensor,
					       const char *match,
					       struct wf_sensor **var)
{
	if (*var == NULL && !strcmp(sensor->name, match)) {
		if (wf_get_sensor(sensor) == 0)
			*var = sensor;
	}
	return *var;
}