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
struct virtchnl_l4_spec {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  tcp_spec; } ;
struct TYPE_6__ {int /*<<< orphan*/  flow_type; TYPE_2__ mask; } ;
struct iavf_cloud_filter {int add; int /*<<< orphan*/  list; TYPE_3__ f; int /*<<< orphan*/  cookie; } ;
struct iavf_adapter {int /*<<< orphan*/  crit_section; int /*<<< orphan*/  cloud_filter_list_lock; int /*<<< orphan*/  aq_required; int /*<<< orphan*/  num_cloud_filters; int /*<<< orphan*/  cloud_filter_list; TYPE_1__* pdev; int /*<<< orphan*/  netdev; } ;
struct flow_cls_offload {int /*<<< orphan*/  cookie; int /*<<< orphan*/  classid; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IAVF_FLAG_AQ_ADD_CLOUD_FILTER ; 
 int /*<<< orphan*/  VIRTCHNL_TCP_V4_FLOW ; 
 int /*<<< orphan*/  __IAVF_IN_CRITICAL_TASK ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int iavf_handle_tclass (struct iavf_adapter*,int,struct iavf_cloud_filter*) ; 
 int iavf_parse_cls_flower (struct iavf_adapter*,struct flow_cls_offload*,struct iavf_cloud_filter*) ; 
 int /*<<< orphan*/  kfree (struct iavf_cloud_filter*) ; 
 struct iavf_cloud_filter* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int tc_classid_to_hwtc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int iavf_configure_clsflower(struct iavf_adapter *adapter,
				    struct flow_cls_offload *cls_flower)
{
	int tc = tc_classid_to_hwtc(adapter->netdev, cls_flower->classid);
	struct iavf_cloud_filter *filter = NULL;
	int err = -EINVAL, count = 50;

	if (tc < 0) {
		dev_err(&adapter->pdev->dev, "Invalid traffic class\n");
		return -EINVAL;
	}

	filter = kzalloc(sizeof(*filter), GFP_KERNEL);
	if (!filter)
		return -ENOMEM;

	while (test_and_set_bit(__IAVF_IN_CRITICAL_TASK,
				&adapter->crit_section)) {
		if (--count == 0)
			goto err;
		udelay(1);
	}

	filter->cookie = cls_flower->cookie;

	/* set the mask to all zeroes to begin with */
	memset(&filter->f.mask.tcp_spec, 0, sizeof(struct virtchnl_l4_spec));
	/* start out with flow type and eth type IPv4 to begin with */
	filter->f.flow_type = VIRTCHNL_TCP_V4_FLOW;
	err = iavf_parse_cls_flower(adapter, cls_flower, filter);
	if (err < 0)
		goto err;

	err = iavf_handle_tclass(adapter, tc, filter);
	if (err < 0)
		goto err;

	/* add filter to the list */
	spin_lock_bh(&adapter->cloud_filter_list_lock);
	list_add_tail(&filter->list, &adapter->cloud_filter_list);
	adapter->num_cloud_filters++;
	filter->add = true;
	adapter->aq_required |= IAVF_FLAG_AQ_ADD_CLOUD_FILTER;
	spin_unlock_bh(&adapter->cloud_filter_list_lock);
err:
	if (err)
		kfree(filter);

	clear_bit(__IAVF_IN_CRITICAL_TASK, &adapter->crit_section);
	return err;
}