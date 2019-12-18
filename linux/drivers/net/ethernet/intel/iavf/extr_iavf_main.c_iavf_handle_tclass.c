#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_5__ {int /*<<< orphan*/  dst_port; } ;
struct TYPE_6__ {TYPE_1__ tcp_spec; } ;
struct TYPE_8__ {scalar_t__ action_meta; int /*<<< orphan*/  action; TYPE_2__ data; } ;
struct iavf_cloud_filter {TYPE_4__ f; } ;
struct iavf_adapter {scalar_t__ num_tc; TYPE_3__* pdev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  VIRTCHNL_ACTION_TC_REDIRECT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int iavf_handle_tclass(struct iavf_adapter *adapter, u32 tc,
			      struct iavf_cloud_filter *filter)
{
	if (tc == 0)
		return 0;
	if (tc < adapter->num_tc) {
		if (!filter->f.data.tcp_spec.dst_port) {
			dev_err(&adapter->pdev->dev,
				"Specify destination port to redirect to traffic class other than TC0\n");
			return -EINVAL;
		}
	}
	/* redirect to a traffic class on the same device */
	filter->f.action = VIRTCHNL_ACTION_TC_REDIRECT;
	filter->f.action_meta = tc;
	return 0;
}