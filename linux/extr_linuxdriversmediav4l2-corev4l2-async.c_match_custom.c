#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct v4l2_subdev {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int (* match ) (int /*<<< orphan*/ ,struct v4l2_async_subdev*) ;} ;
struct TYPE_4__ {TYPE_1__ custom; } ;
struct v4l2_async_subdev {TYPE_2__ match; } ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,struct v4l2_async_subdev*) ; 

__attribute__((used)) static bool match_custom(struct v4l2_subdev *sd, struct v4l2_async_subdev *asd)
{
	if (!asd->match.custom.match)
		/* Match always */
		return true;

	return asd->match.custom.match(sd->dev, asd);
}