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
struct platform_device {int dummy; } ;
struct allegro_dev {int /*<<< orphan*/  v4l2_dev; scalar_t__ m2m_dev; int /*<<< orphan*/  video_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  allegro_free_fw_codec (struct allegro_dev*) ; 
 int /*<<< orphan*/  allegro_mcu_hw_deinit (struct allegro_dev*) ; 
 struct allegro_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  v4l2_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v4l2_m2m_release (scalar_t__) ; 
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int allegro_remove(struct platform_device *pdev)
{
	struct allegro_dev *dev = platform_get_drvdata(pdev);

	video_unregister_device(&dev->video_dev);
	if (dev->m2m_dev)
		v4l2_m2m_release(dev->m2m_dev);
	allegro_mcu_hw_deinit(dev);
	allegro_free_fw_codec(dev);

	v4l2_device_unregister(&dev->v4l2_dev);

	return 0;
}