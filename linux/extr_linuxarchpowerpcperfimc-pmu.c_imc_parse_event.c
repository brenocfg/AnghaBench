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
typedef  scalar_t__ u32 ;
struct imc_events {void* name; void* scale; void* unit; scalar_t__ value; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 void* kasprintf (int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ of_property_read_string (struct device_node*,char*,char const**) ; 
 scalar_t__ of_property_read_u32 (struct device_node*,char*,scalar_t__*) ; 

__attribute__((used)) static int imc_parse_event(struct device_node *np, const char *scale,
				  const char *unit, const char *prefix,
				  u32 base, struct imc_events *event)
{
	const char *s;
	u32 reg;

	if (of_property_read_u32(np, "reg", &reg))
		goto error;
	/* Add the base_reg value to the "reg" */
	event->value = base + reg;

	if (of_property_read_string(np, "event-name", &s))
		goto error;

	event->name = kasprintf(GFP_KERNEL, "%s%s", prefix, s);
	if (!event->name)
		goto error;

	if (of_property_read_string(np, "scale", &s))
		s = scale;

	if (s) {
		event->scale = kstrdup(s, GFP_KERNEL);
		if (!event->scale)
			goto error;
	}

	if (of_property_read_string(np, "unit", &s))
		s = unit;

	if (s) {
		event->unit = kstrdup(s, GFP_KERNEL);
		if (!event->unit)
			goto error;
	}

	return 0;
error:
	kfree(event->unit);
	kfree(event->scale);
	kfree(event->name);
	return -EINVAL;
}