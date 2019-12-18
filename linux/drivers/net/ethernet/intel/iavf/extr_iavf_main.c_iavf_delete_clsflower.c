#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct iavf_cloud_filter {int del; } ;
struct iavf_adapter {int /*<<< orphan*/  cloud_filter_list_lock; int /*<<< orphan*/  aq_required; } ;
struct flow_cls_offload {int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IAVF_FLAG_AQ_DEL_CLOUD_FILTER ; 
 struct iavf_cloud_filter* iavf_find_cf (struct iavf_adapter*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int iavf_delete_clsflower(struct iavf_adapter *adapter,
				 struct flow_cls_offload *cls_flower)
{
	struct iavf_cloud_filter *filter = NULL;
	int err = 0;

	spin_lock_bh(&adapter->cloud_filter_list_lock);
	filter = iavf_find_cf(adapter, &cls_flower->cookie);
	if (filter) {
		filter->del = true;
		adapter->aq_required |= IAVF_FLAG_AQ_DEL_CLOUD_FILTER;
	} else {
		err = -EINVAL;
	}
	spin_unlock_bh(&adapter->cloud_filter_list_lock);

	return err;
}