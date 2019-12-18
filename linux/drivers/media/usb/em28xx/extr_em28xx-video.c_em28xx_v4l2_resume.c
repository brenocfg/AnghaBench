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
struct em28xx {TYPE_1__* intf; int /*<<< orphan*/  has_video; scalar_t__ is_audio_only; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int em28xx_v4l2_resume(struct em28xx *dev)
{
	if (dev->is_audio_only)
		return 0;

	if (!dev->has_video)
		return 0;

	dev_info(&dev->intf->dev, "Resuming video extension\n");
	/* what do we do here */
	return 0;
}