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
struct regmap_field {int dummy; } ;
struct mux_control {int /*<<< orphan*/  chip; } ;

/* Variables and functions */
 struct regmap_field** mux_chip_priv (int /*<<< orphan*/ ) ; 
 size_t mux_control_get_index (struct mux_control*) ; 
 int regmap_field_write (struct regmap_field*,int) ; 

__attribute__((used)) static int mux_mmio_set(struct mux_control *mux, int state)
{
	struct regmap_field **fields = mux_chip_priv(mux->chip);

	return regmap_field_write(fields[mux_control_get_index(mux)], state);
}