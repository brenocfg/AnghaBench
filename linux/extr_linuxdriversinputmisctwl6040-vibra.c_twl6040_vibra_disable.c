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
struct vibra_info {int enabled; int /*<<< orphan*/  supplies; struct twl6040* twl6040; } ;
struct twl6040 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TWL6040_REG_VIBCTLL ; 
 int /*<<< orphan*/  TWL6040_REG_VIBCTLR ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl6040_power (struct twl6040*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl6040_reg_write (struct twl6040*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void twl6040_vibra_disable(struct vibra_info *info)
{
	struct twl6040 *twl6040 = info->twl6040;

	twl6040_reg_write(twl6040, TWL6040_REG_VIBCTLL, 0x00);
	twl6040_reg_write(twl6040, TWL6040_REG_VIBCTLR, 0x00);
	twl6040_power(info->twl6040, 0);

	regulator_bulk_disable(ARRAY_SIZE(info->supplies), info->supplies);

	info->enabled = false;
}