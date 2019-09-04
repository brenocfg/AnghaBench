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
typedef  int u32 ;
struct v4l2_subdev {int dummy; } ;
struct CHIPSTATE {int input; scalar_t__ muted; struct CHIPDESC* desc; } ;
struct CHIPDESC {int flags; int /*<<< orphan*/  inputmask; int /*<<< orphan*/ * inputmap; int /*<<< orphan*/  inputreg; } ;

/* Variables and functions */
 int CHIP_HAS_INPUTSEL ; 
 int EINVAL ; 
 int /*<<< orphan*/  chip_write_masked (struct CHIPSTATE*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct CHIPSTATE* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static int tvaudio_s_routing(struct v4l2_subdev *sd,
			     u32 input, u32 output, u32 config)
{
	struct CHIPSTATE *chip = to_state(sd);
	struct CHIPDESC *desc = chip->desc;

	if (!(desc->flags & CHIP_HAS_INPUTSEL))
		return 0;
	if (input >= 4)
		return -EINVAL;
	/* There are four inputs: tuner, radio, extern and intern. */
	chip->input = input;
	if (chip->muted)
		return 0;
	chip_write_masked(chip, desc->inputreg,
			desc->inputmap[chip->input], desc->inputmask);
	return 0;
}