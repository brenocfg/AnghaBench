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
struct skd_device {int state; TYPE_1__* pdev; int /*<<< orphan*/  queue; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SKD_DRVR_STATE_BUSY 137 
#define  SKD_DRVR_STATE_BUSY_IMMINENT 136 
#define  SKD_DRVR_STATE_ONLINE 135 
#define  SKD_DRVR_STATE_PAUSED 134 
#define  SKD_DRVR_STATE_PAUSING 133 
#define  SKD_DRVR_STATE_RESTARTING 132 
#define  SKD_DRVR_STATE_RESUMING 131 
#define  SKD_DRVR_STATE_STARTING 130 
#define  SKD_DRVR_STATE_STOPPING 129 
#define  SKD_DRVR_STATE_SYNCING 128 
 int /*<<< orphan*/  blk_mq_stop_hw_queues (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int skd_quiesce_dev(struct skd_device *skdev)
{
	int rc = 0;

	switch (skdev->state) {
	case SKD_DRVR_STATE_BUSY:
	case SKD_DRVR_STATE_BUSY_IMMINENT:
		dev_dbg(&skdev->pdev->dev, "stopping queue\n");
		blk_mq_stop_hw_queues(skdev->queue);
		break;
	case SKD_DRVR_STATE_ONLINE:
	case SKD_DRVR_STATE_STOPPING:
	case SKD_DRVR_STATE_SYNCING:
	case SKD_DRVR_STATE_PAUSING:
	case SKD_DRVR_STATE_PAUSED:
	case SKD_DRVR_STATE_STARTING:
	case SKD_DRVR_STATE_RESTARTING:
	case SKD_DRVR_STATE_RESUMING:
	default:
		rc = -EINVAL;
		dev_dbg(&skdev->pdev->dev, "state [%d] not implemented\n",
			skdev->state);
	}
	return rc;
}