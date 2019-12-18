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
struct maple_device {int /*<<< orphan*/  unit; int /*<<< orphan*/  port; int /*<<< orphan*/  dev; int /*<<< orphan*/  (* fileerr_handler ) (struct maple_device*,void*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct maple_device*,void*) ; 

__attribute__((used)) static void maple_response_fileerr(struct maple_device *mdev, void *recvbuf)
{
	if (mdev->fileerr_handler) {
		mdev->fileerr_handler(mdev, recvbuf);
		return;
	} else
		dev_warn(&mdev->dev, "device at (%d, %d) reports"
			"file error 0x%X\n", mdev->port, mdev->unit,
			((int *)recvbuf)[1]);
}