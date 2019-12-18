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
struct cx8800_dev {int /*<<< orphan*/  video_dev; int /*<<< orphan*/  vbi_dev; int /*<<< orphan*/  radio_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  video_unregister_device (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cx8800_unregister_video(struct cx8800_dev *dev)
{
	video_unregister_device(&dev->radio_dev);
	video_unregister_device(&dev->vbi_dev);
	video_unregister_device(&dev->video_dev);
}