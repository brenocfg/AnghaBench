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
struct TYPE_2__ {int tuner; int /*<<< orphan*/  nr; struct mci_base* base; } ;
struct sx8 {TYPE_1__ mci; } ;
struct mci_base {int /*<<< orphan*/  dev; } ;
struct dvb_frontend {struct sx8* demodulator_priv; } ;

/* Variables and functions */
 int EINVAL ; 
 int SX8_TUNER_NUM ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int set_input(struct dvb_frontend *fe, int input)
{
	struct sx8 *state = fe->demodulator_priv;
	struct mci_base *mci_base = state->mci.base;

	if (input >= SX8_TUNER_NUM)
		return -EINVAL;

	state->mci.tuner = input;
	dev_dbg(mci_base->dev, "MCI-%d: input=%d\n", state->mci.nr, input);
	return 0;
}