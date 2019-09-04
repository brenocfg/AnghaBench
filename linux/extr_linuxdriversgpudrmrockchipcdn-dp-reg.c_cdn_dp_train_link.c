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
struct TYPE_2__ {int /*<<< orphan*/  num_lanes; int /*<<< orphan*/  rate; } ;
struct cdn_dp_device {TYPE_1__ link; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEV_DEBUG_KMS (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DRM_DEV_ERROR (int /*<<< orphan*/ ,char*,int) ; 
 int cdn_dp_get_training_status (struct cdn_dp_device*) ; 
 int cdn_dp_training_start (struct cdn_dp_device*) ; 

int cdn_dp_train_link(struct cdn_dp_device *dp)
{
	int ret;

	ret = cdn_dp_training_start(dp);
	if (ret) {
		DRM_DEV_ERROR(dp->dev, "Failed to start training %d\n", ret);
		return ret;
	}

	ret = cdn_dp_get_training_status(dp);
	if (ret) {
		DRM_DEV_ERROR(dp->dev, "Failed to get training stat %d\n", ret);
		return ret;
	}

	DRM_DEV_DEBUG_KMS(dp->dev, "rate:0x%x, lanes:%d\n", dp->link.rate,
			  dp->link.num_lanes);
	return ret;
}