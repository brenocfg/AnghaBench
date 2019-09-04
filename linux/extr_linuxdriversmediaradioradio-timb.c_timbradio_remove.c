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
struct timbradio {int /*<<< orphan*/  v4l2_dev; int /*<<< orphan*/  video_dev; } ;
struct platform_device {int dummy; } ;

/* Variables and functions */
 struct timbradio* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int timbradio_remove(struct platform_device *pdev)
{
	struct timbradio *tr = platform_get_drvdata(pdev);

	video_unregister_device(&tr->video_dev);
	v4l2_device_unregister(&tr->v4l2_dev);
	return 0;
}