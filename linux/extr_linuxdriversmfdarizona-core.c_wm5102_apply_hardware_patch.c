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
struct arizona_sysclk_state {int dummy; } ;
struct arizona {int /*<<< orphan*/  regmap; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_WRITE_SEQUENCER_CTRL_0 ; 
 int /*<<< orphan*/  ARIZONA_WRITE_SEQUENCER_CTRL_1 ; 
 int ARIZONA_WSEQ_ABORT ; 
 int /*<<< orphan*/  ARIZONA_WSEQ_BUSY ; 
 int ARIZONA_WSEQ_ENA ; 
 int ARIZONA_WSEQ_START ; 
 int arizona_disable_freerun_sysclk (struct arizona*,struct arizona_sysclk_state*) ; 
 int arizona_enable_freerun_sysclk (struct arizona*,struct arizona_sysclk_state*) ; 
 int arizona_poll_reg (struct arizona*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm5102_apply_hardware_patch(struct arizona *arizona)
{
	struct arizona_sysclk_state state;
	int err, ret;

	ret = arizona_enable_freerun_sysclk(arizona, &state);
	if (ret)
		return ret;

	/* Start the write sequencer and wait for it to finish */
	ret = regmap_write(arizona->regmap, ARIZONA_WRITE_SEQUENCER_CTRL_0,
			   ARIZONA_WSEQ_ENA | ARIZONA_WSEQ_START | 160);
	if (ret) {
		dev_err(arizona->dev, "Failed to start write sequencer: %d\n",
			ret);
		goto err;
	}

	ret = arizona_poll_reg(arizona, 30, ARIZONA_WRITE_SEQUENCER_CTRL_1,
			       ARIZONA_WSEQ_BUSY, 0);
	if (ret)
		regmap_write(arizona->regmap, ARIZONA_WRITE_SEQUENCER_CTRL_0,
			     ARIZONA_WSEQ_ABORT);

err:
	err = arizona_disable_freerun_sysclk(arizona, &state);

	return ret ?: err;
}