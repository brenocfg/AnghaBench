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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;
struct intel_plane {int (* get_hw_state ) (struct intel_plane*,int*) ;TYPE_1__ base; } ;
typedef  enum pipe { ____Placeholder_pipe } pipe ;

/* Variables and functions */
 int /*<<< orphan*/  I915_STATE_WARN (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  onoff (int) ; 
 int stub1 (struct intel_plane*,int*) ; 

__attribute__((used)) static void assert_plane(struct intel_plane *plane, bool state)
{
	enum pipe pipe;
	bool cur_state;

	cur_state = plane->get_hw_state(plane, &pipe);

	I915_STATE_WARN(cur_state != state,
			"%s assertion failure (expected %s, current %s)\n",
			plane->base.name, onoff(state), onoff(cur_state));
}