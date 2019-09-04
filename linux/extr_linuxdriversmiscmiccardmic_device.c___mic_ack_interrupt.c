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
struct vop_device {int dummy; } ;
struct mic_driver {int /*<<< orphan*/  mdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  mic_ack_interrupt (int /*<<< orphan*/ *) ; 
 struct mic_driver* vpdev_to_mdrv (struct vop_device*) ; 

__attribute__((used)) static void __mic_ack_interrupt(struct vop_device *vpdev, int num)
{
	struct mic_driver *mdrv = vpdev_to_mdrv(vpdev);

	mic_ack_interrupt(&mdrv->mdev);
}