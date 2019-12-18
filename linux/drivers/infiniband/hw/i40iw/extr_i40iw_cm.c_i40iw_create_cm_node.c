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
typedef  void* u16 ;
struct iw_cm_conn_param {void* private_data; int /*<<< orphan*/  ord; int /*<<< orphan*/  ird; void* private_data_len; } ;
struct i40iw_device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  addr; void* size; } ;
struct TYPE_3__ {int client; void* rcv_wscale; void* snd_wscale; int /*<<< orphan*/  rcv_wnd; int /*<<< orphan*/  snd_wnd; int /*<<< orphan*/  max_snd_wnd; int /*<<< orphan*/  loc_seq_num; int /*<<< orphan*/  rcv_nxt; } ;
struct i40iw_cm_node {scalar_t__ ord_size; scalar_t__ ird_size; int /*<<< orphan*/  state; int /*<<< orphan*/  pdata_buf; TYPE_2__ pdata; TYPE_1__ tcp_cntxt; struct i40iw_cm_node* loopbackpartner; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  rem_port; } ;
struct i40iw_cm_listener {int /*<<< orphan*/  cm_id; } ;
struct i40iw_cm_info {int /*<<< orphan*/  ipv4; int /*<<< orphan*/  cm_id; int /*<<< orphan*/  loc_port; int /*<<< orphan*/  rem_port; int /*<<< orphan*/  rem_addr; int /*<<< orphan*/  loc_addr; } ;
struct i40iw_cm_core {int /*<<< orphan*/  stats_loopbacks; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNREFUSED ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct i40iw_cm_node* ERR_PTR (int /*<<< orphan*/ ) ; 
 void* I40IW_CM_DEFAULT_RCV_WND_SCALE ; 
 int /*<<< orphan*/  I40IW_CM_LISTENER_ACTIVE_STATE ; 
 int /*<<< orphan*/  I40IW_CM_STATE_OFFLOADED ; 
 int /*<<< orphan*/  I40IW_CM_STATE_SYN_SENT ; 
 struct i40iw_cm_listener* i40iw_find_listener (struct i40iw_cm_core*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct i40iw_cm_node* i40iw_make_cm_node (struct i40iw_cm_core*,struct i40iw_device*,struct i40iw_cm_info*,struct i40iw_cm_listener*) ; 
 int /*<<< orphan*/  i40iw_record_ird_ord (struct i40iw_cm_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40iw_rem_ref_cm_node (struct i40iw_cm_node*) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,void*) ; 

__attribute__((used)) static struct i40iw_cm_node *i40iw_create_cm_node(
					struct i40iw_cm_core *cm_core,
					struct i40iw_device *iwdev,
					struct iw_cm_conn_param *conn_param,
					struct i40iw_cm_info *cm_info)
{
	struct i40iw_cm_node *cm_node;
	struct i40iw_cm_listener *loopback_remotelistener;
	struct i40iw_cm_node *loopback_remotenode;
	struct i40iw_cm_info loopback_cm_info;

	u16 private_data_len = conn_param->private_data_len;
	const void *private_data = conn_param->private_data;

	/* create a CM connection node */
	cm_node = i40iw_make_cm_node(cm_core, iwdev, cm_info, NULL);
	if (!cm_node)
		return ERR_PTR(-ENOMEM);
	/* set our node side to client (active) side */
	cm_node->tcp_cntxt.client = 1;
	cm_node->tcp_cntxt.rcv_wscale = I40IW_CM_DEFAULT_RCV_WND_SCALE;

	i40iw_record_ird_ord(cm_node, conn_param->ird, conn_param->ord);

	if (!memcmp(cm_info->loc_addr, cm_info->rem_addr, sizeof(cm_info->loc_addr))) {
		loopback_remotelistener = i40iw_find_listener(
						cm_core,
						cm_info->rem_addr,
						cm_node->rem_port,
						cm_node->vlan_id,
						I40IW_CM_LISTENER_ACTIVE_STATE);
		if (!loopback_remotelistener) {
			i40iw_rem_ref_cm_node(cm_node);
			return ERR_PTR(-ECONNREFUSED);
		} else {
			loopback_cm_info = *cm_info;
			loopback_cm_info.loc_port = cm_info->rem_port;
			loopback_cm_info.rem_port = cm_info->loc_port;
			loopback_cm_info.cm_id = loopback_remotelistener->cm_id;
			loopback_cm_info.ipv4 = cm_info->ipv4;
			loopback_remotenode = i40iw_make_cm_node(cm_core,
								 iwdev,
								 &loopback_cm_info,
								 loopback_remotelistener);
			if (!loopback_remotenode) {
				i40iw_rem_ref_cm_node(cm_node);
				return ERR_PTR(-ENOMEM);
			}
			cm_core->stats_loopbacks++;
			loopback_remotenode->loopbackpartner = cm_node;
			loopback_remotenode->tcp_cntxt.rcv_wscale =
				I40IW_CM_DEFAULT_RCV_WND_SCALE;
			cm_node->loopbackpartner = loopback_remotenode;
			memcpy(loopback_remotenode->pdata_buf, private_data,
			       private_data_len);
			loopback_remotenode->pdata.size = private_data_len;

			if (loopback_remotenode->ord_size > cm_node->ird_size)
				loopback_remotenode->ord_size =
					cm_node->ird_size;

			cm_node->state = I40IW_CM_STATE_OFFLOADED;
			cm_node->tcp_cntxt.rcv_nxt =
				loopback_remotenode->tcp_cntxt.loc_seq_num;
			loopback_remotenode->tcp_cntxt.rcv_nxt =
				cm_node->tcp_cntxt.loc_seq_num;
			cm_node->tcp_cntxt.max_snd_wnd =
				loopback_remotenode->tcp_cntxt.rcv_wnd;
			loopback_remotenode->tcp_cntxt.max_snd_wnd = cm_node->tcp_cntxt.rcv_wnd;
			cm_node->tcp_cntxt.snd_wnd = loopback_remotenode->tcp_cntxt.rcv_wnd;
			loopback_remotenode->tcp_cntxt.snd_wnd = cm_node->tcp_cntxt.rcv_wnd;
			cm_node->tcp_cntxt.snd_wscale = loopback_remotenode->tcp_cntxt.rcv_wscale;
			loopback_remotenode->tcp_cntxt.snd_wscale = cm_node->tcp_cntxt.rcv_wscale;
		}
		return cm_node;
	}

	cm_node->pdata.size = private_data_len;
	cm_node->pdata.addr = cm_node->pdata_buf;

	memcpy(cm_node->pdata_buf, private_data, private_data_len);

	cm_node->state = I40IW_CM_STATE_SYN_SENT;
	return cm_node;
}