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
struct scif_hw_dev {int dummy; } ;
struct mic_device {TYPE_1__* ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* send_intr ) (struct mic_device*,int) ;} ;

/* Variables and functions */
 struct mic_device* scdev_to_mdev (struct scif_hw_dev*) ; 
 int /*<<< orphan*/  stub1 (struct mic_device*,int) ; 

__attribute__((used)) static void ___mic_send_intr(struct scif_hw_dev *scdev, int db)
{
	struct mic_device *mdev = scdev_to_mdev(scdev);

	mdev->ops->send_intr(mdev, db);
}