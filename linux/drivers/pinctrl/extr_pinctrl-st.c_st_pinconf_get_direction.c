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
struct st_pio_control {scalar_t__ od; scalar_t__ pu; scalar_t__ oe; } ;

/* Variables and functions */
 unsigned int BIT (int) ; 
 int /*<<< orphan*/  ST_PINCONF_PACK_OD (unsigned long) ; 
 int /*<<< orphan*/  ST_PINCONF_PACK_OE (unsigned long) ; 
 int /*<<< orphan*/  ST_PINCONF_PACK_PU (unsigned long) ; 
 int /*<<< orphan*/  regmap_field_read (scalar_t__,unsigned int*) ; 

__attribute__((used)) static void st_pinconf_get_direction(struct st_pio_control *pc,
	int pin, unsigned long *config)
{
	unsigned int oe_value, pu_value, od_value;

	if (pc->oe) {
		regmap_field_read(pc->oe, &oe_value);
		if (oe_value & BIT(pin))
			ST_PINCONF_PACK_OE(*config);
	}

	if (pc->pu) {
		regmap_field_read(pc->pu, &pu_value);
		if (pu_value & BIT(pin))
			ST_PINCONF_PACK_PU(*config);
	}

	if (pc->od) {
		regmap_field_read(pc->od, &od_value);
		if (od_value & BIT(pin))
			ST_PINCONF_PACK_OD(*config);
	}
}