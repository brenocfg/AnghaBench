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
struct sparcspkr_state {int /*<<< orphan*/  (* event ) (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;struct input_dev* input_dev; } ;
struct platform_device {int dummy; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_SND ; 
 int /*<<< orphan*/  SND_BELL ; 
 struct sparcspkr_state* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  stub1 (struct input_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sparcspkr_shutdown(struct platform_device *dev)
{
	struct sparcspkr_state *state = platform_get_drvdata(dev);
	struct input_dev *input_dev = state->input_dev;

	/* turn off the speaker */
	state->event(input_dev, EV_SND, SND_BELL, 0);
}