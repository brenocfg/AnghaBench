#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct TYPE_4__ {scalar_t__* offset; int num_tc; scalar_t__* count; } ;
struct tc_mqprio_qopt_offload {scalar_t__* max_rate; TYPE_1__ qopt; scalar_t__* min_rate; } ;
struct i40e_vsi {scalar_t__ num_queue_pairs; TYPE_3__* back; } ;
struct TYPE_6__ {TYPE_2__* pdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  I40E_BW_MBPS_DIVISOR ; 
 int I40E_MAX_TRAFFIC_CLASS ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  do_div (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ i40e_get_link_speed (struct i40e_vsi*) ; 

__attribute__((used)) static int i40e_validate_mqprio_qopt(struct i40e_vsi *vsi,
				     struct tc_mqprio_qopt_offload *mqprio_qopt)
{
	u64 sum_max_rate = 0;
	u64 max_rate = 0;
	int i;

	if (mqprio_qopt->qopt.offset[0] != 0 ||
	    mqprio_qopt->qopt.num_tc < 1 ||
	    mqprio_qopt->qopt.num_tc > I40E_MAX_TRAFFIC_CLASS)
		return -EINVAL;
	for (i = 0; ; i++) {
		if (!mqprio_qopt->qopt.count[i])
			return -EINVAL;
		if (mqprio_qopt->min_rate[i]) {
			dev_err(&vsi->back->pdev->dev,
				"Invalid min tx rate (greater than 0) specified\n");
			return -EINVAL;
		}
		max_rate = mqprio_qopt->max_rate[i];
		do_div(max_rate, I40E_BW_MBPS_DIVISOR);
		sum_max_rate += max_rate;

		if (i >= mqprio_qopt->qopt.num_tc - 1)
			break;
		if (mqprio_qopt->qopt.offset[i + 1] !=
		    (mqprio_qopt->qopt.offset[i] + mqprio_qopt->qopt.count[i]))
			return -EINVAL;
	}
	if (vsi->num_queue_pairs <
	    (mqprio_qopt->qopt.offset[i] + mqprio_qopt->qopt.count[i])) {
		return -EINVAL;
	}
	if (sum_max_rate > i40e_get_link_speed(vsi)) {
		dev_err(&vsi->back->pdev->dev,
			"Invalid max tx rate specified\n");
		return -EINVAL;
	}
	return 0;
}