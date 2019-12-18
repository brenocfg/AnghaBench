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
struct imgu_device {int /*<<< orphan*/  media_dev; int /*<<< orphan*/  v4l2_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  IMGU_MAX_PIPE_NUM ; 
 int /*<<< orphan*/  imgu_v4l2_cleanup_pipes (struct imgu_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  media_device_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  media_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 

int imgu_v4l2_unregister(struct imgu_device *imgu)
{
	media_device_unregister(&imgu->media_dev);
	imgu_v4l2_cleanup_pipes(imgu, IMGU_MAX_PIPE_NUM);
	v4l2_device_unregister(&imgu->v4l2_dev);
	media_device_cleanup(&imgu->media_dev);

	return 0;
}