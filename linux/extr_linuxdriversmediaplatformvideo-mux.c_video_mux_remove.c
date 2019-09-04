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
struct v4l2_subdev {int /*<<< orphan*/  entity; } ;
struct video_mux {struct v4l2_subdev subdev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  media_entity_cleanup (int /*<<< orphan*/ *) ; 
 struct video_mux* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  v4l2_async_unregister_subdev (struct v4l2_subdev*) ; 

__attribute__((used)) static int video_mux_remove(struct platform_device *pdev)
{
	struct video_mux *vmux = platform_get_drvdata(pdev);
	struct v4l2_subdev *sd = &vmux->subdev;

	v4l2_async_unregister_subdev(sd);
	media_entity_cleanup(&sd->entity);

	return 0;
}