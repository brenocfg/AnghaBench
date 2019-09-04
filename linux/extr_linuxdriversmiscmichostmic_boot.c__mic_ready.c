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
struct mic_device {TYPE_1__* ops; } ;
struct cosm_device {int dummy; } ;
struct TYPE_2__ {int (* is_fw_ready ) (struct mic_device*) ;} ;

/* Variables and functions */
 struct mic_device* cosmdev_to_mdev (struct cosm_device*) ; 
 int stub1 (struct mic_device*) ; 

__attribute__((used)) static bool _mic_ready(struct cosm_device *cdev)
{
	struct mic_device *mdev = cosmdev_to_mdev(cdev);

	return mdev->ops->is_fw_ready(mdev);
}