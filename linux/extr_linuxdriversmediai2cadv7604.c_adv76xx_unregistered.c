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
struct adv76xx_state {int /*<<< orphan*/  cec_adap; } ;

/* Variables and functions */
 int /*<<< orphan*/  cec_unregister_adapter (int /*<<< orphan*/ ) ; 
 struct adv76xx_state* to_state (struct v4l2_subdev*) ; 

__attribute__((used)) static void adv76xx_unregistered(struct v4l2_subdev *sd)
{
	struct adv76xx_state *state = to_state(sd);

	cec_unregister_adapter(state->cec_adap);
}