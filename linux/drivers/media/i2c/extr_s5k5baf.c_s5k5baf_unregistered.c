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
struct s5k5baf {int /*<<< orphan*/  cis_sd; } ;

/* Variables and functions */
 struct s5k5baf* to_s5k5baf (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void s5k5baf_unregistered(struct v4l2_subdev *sd)
{
	struct s5k5baf *state = to_s5k5baf(sd);
	v4l2_device_unregister_subdev(&state->cis_sd);
}