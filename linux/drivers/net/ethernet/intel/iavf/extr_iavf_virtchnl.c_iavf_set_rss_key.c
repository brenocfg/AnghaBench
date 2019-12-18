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
typedef  int /*<<< orphan*/  u8 ;
struct virtchnl_rss_key {int key_len; int /*<<< orphan*/  key; int /*<<< orphan*/  vsi_id; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct iavf_adapter {scalar_t__ current_op; int rss_key_size; int /*<<< orphan*/  aq_required; int /*<<< orphan*/  rss_key; TYPE_2__ vsi; TYPE_1__* pdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IAVF_FLAG_AQ_SET_RSS_KEY ; 
 scalar_t__ VIRTCHNL_OP_CONFIG_RSS_KEY ; 
 scalar_t__ VIRTCHNL_OP_UNKNOWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  iavf_send_pf_msg (struct iavf_adapter*,scalar_t__,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kfree (struct virtchnl_rss_key*) ; 
 struct virtchnl_rss_key* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void iavf_set_rss_key(struct iavf_adapter *adapter)
{
	struct virtchnl_rss_key *vrk;
	int len;

	if (adapter->current_op != VIRTCHNL_OP_UNKNOWN) {
		/* bail because we already have a command pending */
		dev_err(&adapter->pdev->dev, "Cannot set RSS key, command %d pending\n",
			adapter->current_op);
		return;
	}
	len = sizeof(struct virtchnl_rss_key) +
	      (adapter->rss_key_size * sizeof(u8)) - 1;
	vrk = kzalloc(len, GFP_KERNEL);
	if (!vrk)
		return;
	vrk->vsi_id = adapter->vsi.id;
	vrk->key_len = adapter->rss_key_size;
	memcpy(vrk->key, adapter->rss_key, adapter->rss_key_size);

	adapter->current_op = VIRTCHNL_OP_CONFIG_RSS_KEY;
	adapter->aq_required &= ~IAVF_FLAG_AQ_SET_RSS_KEY;
	iavf_send_pf_msg(adapter, VIRTCHNL_OP_CONFIG_RSS_KEY, (u8 *)vrk, len);
	kfree(vrk);
}