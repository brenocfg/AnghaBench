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
struct s5c73m3 {int /*<<< orphan*/  sensor_sd; } ;

/* Variables and functions */
 struct s5c73m3* oif_sd_to_s5c73m3 (struct v4l2_subdev*) ; 
 int /*<<< orphan*/  v4l2_device_unregister_subdev (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void s5c73m3_oif_unregistered(struct v4l2_subdev *sd)
{
	struct s5c73m3 *state = oif_sd_to_s5c73m3(sd);
	v4l2_device_unregister_subdev(&state->sensor_sd);
}