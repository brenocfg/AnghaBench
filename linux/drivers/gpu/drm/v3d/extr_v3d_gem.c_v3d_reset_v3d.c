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
struct v3d_dev {scalar_t__ reset; } ;

/* Variables and functions */
 int /*<<< orphan*/  reset_control_reset (scalar_t__) ; 
 int /*<<< orphan*/  v3d_init_hw_state (struct v3d_dev*) ; 
 int /*<<< orphan*/  v3d_reset_by_bridge (struct v3d_dev*) ; 

__attribute__((used)) static void
v3d_reset_v3d(struct v3d_dev *v3d)
{
	if (v3d->reset)
		reset_control_reset(v3d->reset);
	else
		v3d_reset_by_bridge(v3d);

	v3d_init_hw_state(v3d);
}