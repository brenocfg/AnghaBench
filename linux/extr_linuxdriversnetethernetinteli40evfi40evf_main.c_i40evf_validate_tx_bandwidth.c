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
struct i40evf_adapter {int link_speed; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
#define  I40E_LINK_SPEED_100MB 133 
#define  I40E_LINK_SPEED_10GB 132 
#define  I40E_LINK_SPEED_1GB 131 
#define  I40E_LINK_SPEED_20GB 130 
#define  I40E_LINK_SPEED_25GB 129 
#define  I40E_LINK_SPEED_40GB 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int i40evf_validate_tx_bandwidth(struct i40evf_adapter *adapter,
					u64 max_tx_rate)
{
	int speed = 0, ret = 0;

	switch (adapter->link_speed) {
	case I40E_LINK_SPEED_40GB:
		speed = 40000;
		break;
	case I40E_LINK_SPEED_25GB:
		speed = 25000;
		break;
	case I40E_LINK_SPEED_20GB:
		speed = 20000;
		break;
	case I40E_LINK_SPEED_10GB:
		speed = 10000;
		break;
	case I40E_LINK_SPEED_1GB:
		speed = 1000;
		break;
	case I40E_LINK_SPEED_100MB:
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