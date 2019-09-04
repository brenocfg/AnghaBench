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
struct v4l2_subdev {int /*<<< orphan*/  v4l2_dev; } ;
struct cobalt {TYPE_1__* streams; } ;
struct TYPE_2__ {struct v4l2_subdev* sd; } ;

/* Variables and functions */
 unsigned int COBALT_NUM_NODES ; 
 int /*<<< orphan*/  cobalt_err (char*) ; 
 struct cobalt* to_cobalt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned cobalt_get_sd_nr(struct v4l2_subdev *sd)
{
	struct cobalt *cobalt = to_cobalt(sd->v4l2_dev);
	unsigned i;

	for (i = 0; i < COBALT_NUM_NODES; i++)
		if (sd == cobalt->streams[i].sd)
			return i;
	cobalt_err("Invalid adv7604 subdev pointer!\n");
	return 0;
}