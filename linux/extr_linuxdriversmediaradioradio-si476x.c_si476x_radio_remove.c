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
struct TYPE_2__ {int /*<<< orphan*/  ctrl_handler; } ;
struct si476x_radio {int /*<<< orphan*/  debugfs; int /*<<< orphan*/  v4l2dev; TYPE_1__ videodev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  debugfs_remove_recursive (int /*<<< orphan*/ ) ; 
 struct si476x_radio* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  v4l2_ctrl_handler_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (TYPE_1__*) ; 

__attribute__((used)) static int si476x_radio_remove(struct platform_device *pdev)
{
	struct si476x_radio *radio = platform_get_drvdata(pdev);

	v4l2_ctrl_handler_free(radio->videodev.ctrl_handler);
	video_unregister_device(&radio->videodev);
	v4l2_device_unregister(&radio->v4l2dev);
	debugfs_remove_recursive(radio->debugfs);

	return 0;
}