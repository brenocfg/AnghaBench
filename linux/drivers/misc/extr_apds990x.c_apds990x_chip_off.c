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
struct apds990x_chip {int /*<<< orphan*/  regs; } ;

/* Variables and functions */
 int /*<<< orphan*/  APDS990X_ENABLE ; 
 int /*<<< orphan*/  APDS990X_EN_DISABLE_ALL ; 
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  apds990x_write_byte (struct apds990x_chip*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regulator_bulk_disable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int apds990x_chip_off(struct apds990x_chip *chip)
{
	apds990x_write_byte(chip, APDS990X_ENABLE, APDS990X_EN_DISABLE_ALL);
	regulator_bulk_disable(ARRAY_SIZE(chip->regs), chip->regs);
	return 0;
}