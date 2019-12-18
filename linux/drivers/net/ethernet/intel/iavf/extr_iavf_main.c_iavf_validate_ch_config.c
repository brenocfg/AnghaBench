#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_4__ {int num_tc; int* offset; scalar_t__* count; } ;
struct tc_mqprio_qopt_offload {TYPE_2__ qopt; int /*<<< orphan*/ * max_rate; scalar_t__* min_rate; } ;
struct iavf_adapter {TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int IAVF_MAX_REQ_QUEUES ; 
 int IAVF_MAX_TRAFFIC_CLASS ; 
 int /*<<< orphan*/  IAVF_MBPS_DIVISOR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ div_u64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iavf_validate_tx_bandwidth (struct iavf_adapter*,scalar_t__) ; 

__attribute__((used)) static int iavf_validate_ch_config(struct iavf_adapter *adapter,
				   struct tc_mqprio_qopt_offload *mqprio_qopt)
{
	u64 total_max_rate = 0;
	int i, num_qps = 0;
	u64 tx_rate = 0;
	int ret = 0;

	if (mqprio_qopt->qopt.num_tc > IAVF_MAX_TRAFFIC_CLASS ||
	    mqprio_qopt->qopt.num_tc < 1)
		return -EINVAL;

	for (i = 0; i <= mqprio_qopt->qopt.num_tc - 1; i++) {
		if (!mqprio_qopt->qopt.count[i] ||
		    mqprio_qopt->qopt.offset[i] != num_qps)
			return -EINVAL;
		if (mqprio_qopt->min_rate[i]) {
			dev_err(&adapter->pdev->dev,
				"Invalid min tx rate (greater than 0) specified\n");
			return -EINVAL;
		}
		/*convert to Mbps */
		tx_rate = div_u64(mqprio_qopt->max_rate[i],
				  IAVF_MBPS_DIVISOR);
		total_max_rate += tx_rate;
		num_qps += mqprio_qopt->qopt.count[i];
	}
	if (num_qps > IAVF_MAX_REQ_QUEUES)
		return -EINVAL;

	ret = iavf_validate_tx_bandwidth(adapter, total_max_rate);
	return ret;
}