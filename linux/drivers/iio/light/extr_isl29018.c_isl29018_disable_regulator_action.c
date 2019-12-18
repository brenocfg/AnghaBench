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
struct isl29018_chip {int /*<<< orphan*/  vcc_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_err (char*) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isl29018_disable_regulator_action(void *_data)
{
	struct isl29018_chip *chip = _data;
	int err;

	err = regulator_disable(chip->vcc_reg);
	if (err)
		pr_err("failed to disable isl29018's VCC regulator!\n");
}