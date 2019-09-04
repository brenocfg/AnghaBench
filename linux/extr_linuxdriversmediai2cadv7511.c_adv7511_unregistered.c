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
struct v4l2_subdev {int dummy; } ;
struct adv7511_state {int /*<<< orphan*/  cec_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  cec_unregister_adapter (int /*<<< orphan*/ ) ; 
 struct adv7511_state* get_adv7511_state (struct v4l2_subdev*) ; 

__attribute__((used)) static void adv7511_unregistered(struct v4l2_subdev *sd)
{
	struct adv7511_state *state = get_adv7511_state(sd);

	cec_unregister_adapter(state->cec_adap);
}