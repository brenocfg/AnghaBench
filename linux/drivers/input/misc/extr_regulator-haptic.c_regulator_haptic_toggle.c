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
struct regulator_haptic {int active; int /*<<< orphan*/  dev; int /*<<< orphan*/  regulator; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,char*,int) ; 
 int regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int regulator_haptic_toggle(struct regulator_haptic *haptic, bool on)
{
	int error;

	if (haptic->active != on) {

		error = on ? regulator_enable(haptic->regulator) :
			     regulator_disable(haptic->regulator);
		if (error) {
			dev_err(haptic->dev,
				"failed to switch regulator %s: %d\n",
				on ? "on" : "off", error);
			return error;
		}

		haptic->active = on;
	}

	return 0;
}