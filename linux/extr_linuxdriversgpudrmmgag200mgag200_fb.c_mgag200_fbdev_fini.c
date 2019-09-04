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
struct mga_device {int /*<<< orphan*/  mfbdev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mga_fbdev_destroy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mgag200_fbdev_fini(struct mga_device *mdev)
{
	if (!mdev->mfbdev)
		return;

	mga_fbdev_destroy(mdev->dev, mdev->mfbdev);
}