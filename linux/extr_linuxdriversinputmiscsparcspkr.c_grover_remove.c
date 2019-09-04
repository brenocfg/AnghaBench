#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct grover_beep_info {int /*<<< orphan*/  freq_regs; int /*<<< orphan*/  enable_reg; } ;
struct TYPE_2__ {struct grover_beep_info grover; } ;
struct sparcspkr_state {int /*<<< orphan*/  (* event ) (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct input_dev* input_dev; TYPE_1__ u; } ;
struct platform_device {int /*<<< orphan*/ * resource; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_SND ; 
 int /*<<< orphan*/  SND_BELL ; 
 int /*<<< orphan*/  input_unregister_device (struct input_dev*) ; 
 int /*<<< orphan*/  kfree (struct sparcspkr_state*) ; 
 int /*<<< orphan*/  of_iounmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct sparcspkr_state* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int grover_remove(struct platform_device *op)
{
	struct sparcspkr_state *state = platform_get_drvdata(op);
	struct grover_beep_info *info = &state->u.grover;
	struct input_dev *input_dev = state->input_dev;

	/* turn off the speaker */
	state->event(input_dev, EV_SND, SND_BELL, 0);

	input_unregister_device(input_dev);

	of_iounmap(&op->resource[3], info->enable_reg, 1);
	of_iounmap(&op->resource[2], info->freq_regs, 2);

	kfree(state);

	return 0;
}