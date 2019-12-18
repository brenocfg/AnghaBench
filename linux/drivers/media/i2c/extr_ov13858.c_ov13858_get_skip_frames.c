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
typedef  int /*<<< orphan*/  u32 ;
struct v4l2_subdev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  OV13858_NUM_OF_SKIP_FRAMES ; 

__attribute__((used)) static int ov13858_get_skip_frames(struct v4l2_subdev *sd, u32 *frames)
{
	*frames = OV13858_NUM_OF_SKIP_FRAMES;

	return 0;
}