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
struct mic_device {int /*<<< orphan*/  dma_mbdev; int /*<<< orphan*/  scdev; int /*<<< orphan*/  vpdev; } ;
struct cosm_device {int dummy; } ;

/* Variables and functions */
 struct mic_device* cosmdev_to_mdev (struct cosm_device*) ; 
 int /*<<< orphan*/  mbus_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mic_bootparam_init (struct mic_device*) ; 
 int /*<<< orphan*/  mic_free_dma_chans (struct mic_device*) ; 
 int /*<<< orphan*/  scif_unregister_device (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vop_unregister_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _mic_stop(struct cosm_device *cdev, bool force)
{
	struct mic_device *mdev = cosmdev_to_mdev(cdev);

	/*
	 * Since SCIF handles card shutdown and reset (using COSM), it will
	 * will be the first to be registered and the last to be
	 * unregistered.
	 */
	vop_unregister_device(mdev->vpdev);
	scif_unregister_device(mdev->scdev);
	mic_free_dma_chans(mdev);
	mbus_unregister_device(mdev->dma_mbdev);
	mic_bootparam_init(mdev);
}