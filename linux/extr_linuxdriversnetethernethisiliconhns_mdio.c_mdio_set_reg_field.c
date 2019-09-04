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
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  mdio_read_reg (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio_set_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdio_write_reg (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mdio_set_reg_field(void *base, u32 reg, u32 mask, u32 shift,
			       u32 val)
{
	u32 origin = mdio_read_reg(base, reg);

	mdio_set_field(origin, mask, shift, val);
	mdio_write_reg(base, reg, origin);
}