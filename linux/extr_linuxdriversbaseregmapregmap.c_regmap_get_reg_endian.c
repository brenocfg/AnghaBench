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
struct regmap_config {int reg_format_endian; } ;
struct regmap_bus {int reg_format_endian_default; } ;
typedef  enum regmap_endian { ____Placeholder_regmap_endian } regmap_endian ;

/* Variables and functions */
 int REGMAP_ENDIAN_BIG ; 
 int REGMAP_ENDIAN_DEFAULT ; 

__attribute__((used)) static enum regmap_endian regmap_get_reg_endian(const struct regmap_bus *bus,
					const struct regmap_config *config)
{
	enum regmap_endian endian;

	/* Retrieve the endianness specification from the regmap config */
	endian = config->reg_format_endian;

	/* If the regmap config specified a non-default value, use that */
	if (endian != REGMAP_ENDIAN_DEFAULT)
		return endian;

	/* Retrieve the endianness specification from the bus config */
	if (bus && bus->reg_format_endian_default)
		endian = bus->reg_format_endian_default;

	/* If the bus specified a non-default value, use that */
	if (endian != REGMAP_ENDIAN_DEFAULT)
		return endian;

	/* Use this if no other value was found */
	return REGMAP_ENDIAN_BIG;
}