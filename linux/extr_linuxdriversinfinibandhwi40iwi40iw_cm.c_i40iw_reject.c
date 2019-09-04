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
typedef  void* u8 ;
struct iw_cm_id {int /*<<< orphan*/  device; scalar_t__ provider_data; } ;
struct ietf_mpa_v2 {int dummy; } ;
struct i40iw_device {int dummy; } ;
struct TYPE_4__ {void* size; } ;
struct i40iw_cm_node {TYPE_2__ pdata; int /*<<< orphan*/  pdata_buf; TYPE_1__* cm_core; struct iw_cm_id* cm_id; struct i40iw_cm_node* loopbackpartner; } ;
struct TYPE_3__ {int /*<<< orphan*/  stats_rejects; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ MAX_CM_BUFFER ; 
 int i40iw_cm_reject (struct i40iw_cm_node*,void const*,void*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,void*) ; 
 struct i40iw_device* to_iwdev (int /*<<< orphan*/ ) ; 

int i40iw_reject(struct iw_cm_id *cm_id, const void *pdata, u8 pdata_len)
{
	struct i40iw_device *iwdev;
	struct i40iw_cm_node *cm_node;
	struct i40iw_cm_node *loopback;

	cm_node = (struct i40iw_cm_node *)cm_id->provider_data;
	loopback = cm_node->loopbackpartner;
	cm_node->cm_id = cm_id;
	cm_node->pdata.size = pdata_len;

	iwdev = to_iwdev(cm_id->device);
	if (!iwdev)
		return -EINVAL;
	cm_node->cm_core->stats_rejects++;

	if (pdata_len + sizeof(struct ietf_mpa_v2) > MAX_CM_BUFFER)
		return -EINVAL;

	if (loopback) {
		memcpy(&loopback->pdata_buf, pdata, pdata_len);
		loopback->pdata.size = pdata_len;
	}

	return i40iw_cm_reject(cm_node, pdata, pdata_len);
}