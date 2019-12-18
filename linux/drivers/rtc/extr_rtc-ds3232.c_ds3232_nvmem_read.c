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
struct regmap {int dummy; } ;

/* Variables and functions */
 scalar_t__ DS3232_REG_SRAM_START ; 
 int regmap_bulk_read (struct regmap*,scalar_t__,void*,size_t) ; 

__attribute__((used)) static int ds3232_nvmem_read(void *priv, unsigned int offset, void *val,
			     size_t bytes)
{
	struct regmap *ds3232_regmap = (struct regmap *)priv;

	return regmap_bulk_read(ds3232_regmap, DS3232_REG_SRAM_START + offset,
				val, bytes);
}