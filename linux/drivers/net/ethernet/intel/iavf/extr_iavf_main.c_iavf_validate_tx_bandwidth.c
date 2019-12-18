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
typedef  int u64 ;
struct iavf_adapter {int link_speed; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  IAVF_LINK_SPEED_100MB 133 
#define  IAVF_LINK_SPEED_10GB 132 
#define  IAVF_LINK_SPEED_1GB 131 
#define  IAVF_LINK_SPEED_20GB 130 
#define  IAVF_LINK_SPEED_25GB 129 
#define  IAVF_LINK_SPEED_40GB 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int iavf_validate_tx_bandwidth(struct iavf_adapter *adapter,
				      u64 max_tx_rate)
{
	int speed = 0, ret = 0;

	switch (adapter->link_speed) {
	case IAVF_LINK_SPEED_40GB:
		speed = 40000;
		break;
	case IAVF_LINK_SPEED_25GB:
		speed = 25000;
		break;
	case IAVF_LINK_SPEED_20GB:
		speed = 20000;
		break;
	case IAVF_LINK_SPEED_10GB:
		speed = 10000;
		break;
	case IAVF_LINK_SPEED_1GB:
		speed = 1000;
		break;
	case IAVF_LINK_SPEED_100MB:
		speed = 100;
		break;
	default:
		break;
	}

	if (max_tx_rate > speed) {
		dev_err(&adapter->pdev->dev,
			"Invalid tx rate specified\n");
		ret = -EINVAL;
	}

	return ret;
}