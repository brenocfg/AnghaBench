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
struct arizona {int /*<<< orphan*/  dev; int /*<<< orphan*/  dcvdd; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_WRITE_SEQUENCER_CTRL_3 ; 
 int /*<<< orphan*/  arizona_disable_reset (struct arizona*) ; 
 int /*<<< orphan*/  arizona_enable_reset (struct arizona*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  regulator_disable (int /*<<< orphan*/ ) ; 
 int regulator_enable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm5102_clear_write_sequencer(struct arizona *arizona)
{
	int ret;

	ret = regmap_write(arizona->regmap, ARIZONA_WRITE_SEQUENCER_CTRL_3,
			   0x0);
	if (ret) {
		dev_err(arizona->dev,
			"Failed to clear write sequencer state: %d\n", ret);
		return ret;
	}

	arizona_enable_reset(arizona);
	regulator_disable(arizona->dcvdd);

	msleep(20);

	ret = regulator_enable(arizona->dcvdd);
	if (ret) {
		dev_err(arizona->dev, "Failed to re-enable DCVDD: %d\n", ret);
		return ret;
	}
	arizona_disable_reset(arizona);

	return 0;
}