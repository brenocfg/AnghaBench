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
typedef  int v4l2_std_id ;
struct v4l2_subdev {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  height; } ;
struct tvp5150 {int norm; TYPE_1__ rect; } ;

/* Variables and functions */
 int /*<<< orphan*/  TVP5150_V_MAX_525_60 ; 
 int /*<<< orphan*/  TVP5150_V_MAX_OTHERS ; 
 int V4L2_STD_525_60 ; 
 struct tvp5150* to_tvp5150 (struct v4l2_subdev*) ; 
 int tvp5150_set_std (struct v4l2_subdev*,int) ; 

__attribute__((used)) static int tvp5150_s_std(struct v4l2_subdev *sd, v4l2_std_id std)
{
	struct tvp5150 *decoder = to_tvp5150(sd);

	if (decoder->norm == std)
		return 0;

	/* Change cropping height limits */
	if (std & V4L2_STD_525_60)
		decoder->rect.height = TVP5150_V_MAX_525_60;
	else
		decoder->rect.height = TVP5150_V_MAX_OTHERS;

	decoder->norm = std;

	return tvp5150_set_std(sd, std);
}