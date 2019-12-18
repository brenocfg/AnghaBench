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
struct v4l2_subdev {scalar_t__ fwnode; } ;
struct TYPE_2__ {scalar_t__ fwnode; } ;
struct v4l2_async_subdev {TYPE_1__ match; } ;

/* Variables and functions */

__attribute__((used)) static bool match_fwnode(struct v4l2_subdev *sd, struct v4l2_async_subdev *asd)
{
	return sd->fwnode == asd->match.fwnode;
}