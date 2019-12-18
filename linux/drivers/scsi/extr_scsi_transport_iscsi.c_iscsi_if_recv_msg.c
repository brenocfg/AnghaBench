#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct nlmsghdr {int nlmsg_type; } ;
struct TYPE_12__ {int /*<<< orphan*/  data_size; int /*<<< orphan*/  hdr_size; int /*<<< orphan*/  cid; int /*<<< orphan*/  sid; } ;
struct TYPE_20__ {int /*<<< orphan*/  flag; int /*<<< orphan*/  cid; int /*<<< orphan*/  sid; } ;
struct TYPE_17__ {int /*<<< orphan*/  cid; int /*<<< orphan*/  sid; } ;
struct TYPE_16__ {int /*<<< orphan*/  transport_eph; int /*<<< orphan*/  is_leading; int /*<<< orphan*/  cid; int /*<<< orphan*/  sid; } ;
struct TYPE_15__ {int /*<<< orphan*/  sid; } ;
struct TYPE_14__ {int /*<<< orphan*/  queue_depth; int /*<<< orphan*/  cmds_max; int /*<<< orphan*/  initial_cmdsn; int /*<<< orphan*/  ep_handle; } ;
struct TYPE_13__ {int /*<<< orphan*/  queue_depth; int /*<<< orphan*/  cmds_max; int /*<<< orphan*/  initial_cmdsn; } ;
struct TYPE_19__ {TYPE_1__ send_pdu; TYPE_9__ stop_conn; TYPE_6__ start_conn; TYPE_5__ b_conn; TYPE_4__ d_session; TYPE_3__ c_bound_session; TYPE_2__ c_session; } ;
struct TYPE_18__ {int /*<<< orphan*/  retcode; } ;
struct iscsi_uevent {TYPE_8__ u; TYPE_7__ r; int /*<<< orphan*/  transport_handle; } ;
struct iscsi_transport {int /*<<< orphan*/  owner; int /*<<< orphan*/  (* send_pdu ) (struct iscsi_cls_conn*,struct iscsi_hdr*,char*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* stop_conn ) (struct iscsi_cls_conn*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* start_conn ) (struct iscsi_cls_conn*) ;int /*<<< orphan*/  ep_connect; int /*<<< orphan*/  (* bind_conn ) (struct iscsi_cls_session*,struct iscsi_cls_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* destroy_session ) (struct iscsi_cls_session*) ;} ;
struct iscsi_internal {struct iscsi_transport* iscsi_transport; } ;
struct iscsi_hdr {int dummy; } ;
struct iscsi_endpoint {struct iscsi_cls_conn* conn; int /*<<< orphan*/  id; } ;
struct iscsi_cls_session {int /*<<< orphan*/  unbind_work; } ;
struct iscsi_cls_conn {int /*<<< orphan*/  ep_mutex; struct iscsi_endpoint* ep; } ;
struct TYPE_11__ {int /*<<< orphan*/  portid; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  ISCSI_NL_GRP_ISCSID ; 
 int /*<<< orphan*/  ISCSI_NL_GRP_UIP ; 
#define  ISCSI_UEVENT_BIND_CONN 158 
#define  ISCSI_UEVENT_CREATE_BOUND_SESSION 157 
#define  ISCSI_UEVENT_CREATE_CONN 156 
#define  ISCSI_UEVENT_CREATE_SESSION 155 
#define  ISCSI_UEVENT_DELETE_CHAP 154 
#define  ISCSI_UEVENT_DEL_FLASHNODE 153 
#define  ISCSI_UEVENT_DESTROY_CONN 152 
#define  ISCSI_UEVENT_DESTROY_SESSION 151 
#define  ISCSI_UEVENT_GET_CHAP 150 
#define  ISCSI_UEVENT_GET_HOST_STATS 149 
#define  ISCSI_UEVENT_GET_STATS 148 
#define  ISCSI_UEVENT_LOGIN_FLASHNODE 147 
#define  ISCSI_UEVENT_LOGOUT_FLASHNODE 146 
#define  ISCSI_UEVENT_LOGOUT_FLASHNODE_SID 145 
#define  ISCSI_UEVENT_NEW_FLASHNODE 144 
#define  ISCSI_UEVENT_PATH_UPDATE 143 
#define  ISCSI_UEVENT_PING 142 
#define  ISCSI_UEVENT_SEND_PDU 141 
#define  ISCSI_UEVENT_SET_CHAP 140 
#define  ISCSI_UEVENT_SET_FLASHNODE_PARAMS 139 
#define  ISCSI_UEVENT_SET_HOST_PARAM 138 
#define  ISCSI_UEVENT_SET_IFACE_PARAMS 137 
#define  ISCSI_UEVENT_SET_PARAM 136 
#define  ISCSI_UEVENT_START_CONN 135 
#define  ISCSI_UEVENT_STOP_CONN 134 
#define  ISCSI_UEVENT_TGT_DSCVR 133 
#define  ISCSI_UEVENT_TRANSPORT_EP_CONNECT 132 
#define  ISCSI_UEVENT_TRANSPORT_EP_CONNECT_THROUGH_HOST 131 
#define  ISCSI_UEVENT_TRANSPORT_EP_DISCONNECT 130 
#define  ISCSI_UEVENT_TRANSPORT_EP_POLL 129 
#define  ISCSI_UEVENT_UNBIND_SESSION 128 
 int /*<<< orphan*/  KERN_ERR ; 
 TYPE_10__ NETLINK_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  iscsi_cls_conn_printk (int /*<<< orphan*/ ,struct iscsi_cls_conn*,char*) ; 
 struct iscsi_cls_conn* iscsi_conn_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iscsi_del_flashnode (struct iscsi_transport*,struct iscsi_uevent*) ; 
 int iscsi_delete_chap (struct iscsi_transport*,struct iscsi_uevent*) ; 
 int iscsi_get_chap (struct iscsi_transport*,struct nlmsghdr*) ; 
 int iscsi_get_host_stats (struct iscsi_transport*,struct nlmsghdr*) ; 
 int iscsi_if_create_conn (struct iscsi_transport*,struct iscsi_uevent*) ; 
 int iscsi_if_create_session (struct iscsi_internal*,struct iscsi_endpoint*,struct iscsi_uevent*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int iscsi_if_destroy_conn (struct iscsi_transport*,struct iscsi_uevent*) ; 
 int /*<<< orphan*/  iscsi_if_ep_disconnect (struct iscsi_transport*,int /*<<< orphan*/ ) ; 
 int iscsi_if_get_stats (struct iscsi_transport*,struct nlmsghdr*) ; 
 int iscsi_if_transport_ep (struct iscsi_transport*,struct iscsi_uevent*,int) ; 
 struct iscsi_internal* iscsi_if_transport_lookup (int /*<<< orphan*/ ) ; 
 int iscsi_login_flashnode (struct iscsi_transport*,struct iscsi_uevent*) ; 
 int iscsi_logout_flashnode (struct iscsi_transport*,struct iscsi_uevent*) ; 
 int iscsi_logout_flashnode_sid (struct iscsi_transport*,struct iscsi_uevent*) ; 
 struct iscsi_endpoint* iscsi_lookup_endpoint (int /*<<< orphan*/ ) ; 
 int iscsi_new_flashnode (struct iscsi_transport*,struct iscsi_uevent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_ptr (int /*<<< orphan*/ ) ; 
 int iscsi_send_ping (struct iscsi_transport*,struct iscsi_uevent*) ; 
 struct iscsi_cls_session* iscsi_session_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iscsi_session_to_shost (struct iscsi_cls_session*) ; 
 int iscsi_set_chap (struct iscsi_transport*,struct iscsi_uevent*,int /*<<< orphan*/ ) ; 
 int iscsi_set_flashnode_param (struct iscsi_transport*,struct iscsi_uevent*,int /*<<< orphan*/ ) ; 
 int iscsi_set_host_param (struct iscsi_transport*,struct iscsi_uevent*) ; 
 int iscsi_set_iface_params (struct iscsi_transport*,struct iscsi_uevent*,int /*<<< orphan*/ ) ; 
 int iscsi_set_param (struct iscsi_transport*,struct iscsi_uevent*) ; 
 int iscsi_set_path (struct iscsi_transport*,struct iscsi_uevent*) ; 
 int iscsi_tgt_dscvr (struct iscsi_transport*,struct iscsi_uevent*) ; 
 int /*<<< orphan*/  module_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlmsg_attrlen (struct nlmsghdr*,int) ; 
 struct iscsi_uevent* nlmsg_data (struct nlmsghdr*) ; 
 int /*<<< orphan*/  scsi_queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct iscsi_cls_session*) ; 
 int /*<<< orphan*/  stub2 (struct iscsi_cls_session*,struct iscsi_cls_conn*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct iscsi_cls_conn*) ; 
 int /*<<< orphan*/  stub4 (struct iscsi_cls_conn*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (struct iscsi_cls_conn*,struct iscsi_hdr*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iscsi_if_recv_msg(struct sk_buff *skb, struct nlmsghdr *nlh, uint32_t *group)
{
	int err = 0;
	u32 portid;
	struct iscsi_uevent *ev = nlmsg_data(nlh);
	struct iscsi_transport *transport = NULL;
	struct iscsi_internal *priv;
	struct iscsi_cls_session *session;
	struct iscsi_cls_conn *conn;
	struct iscsi_endpoint *ep = NULL;

	if (nlh->nlmsg_type == ISCSI_UEVENT_PATH_UPDATE)
		*group = ISCSI_NL_GRP_UIP;
	else
		*group = ISCSI_NL_GRP_ISCSID;

	priv = iscsi_if_transport_lookup(iscsi_ptr(ev->transport_handle));
	if (!priv)
		return -EINVAL;
	transport = priv->iscsi_transport;

	if (!try_module_get(transport->owner))
		return -EINVAL;

	portid = NETLINK_CB(skb).portid;

	switch (nlh->nlmsg_type) {
	case ISCSI_UEVENT_CREATE_SESSION:
		err = iscsi_if_create_session(priv, ep, ev,
					      portid,
					      ev->u.c_session.initial_cmdsn,
					      ev->u.c_session.cmds_max,
					      ev->u.c_session.queue_depth);
		break;
	case ISCSI_UEVENT_CREATE_BOUND_SESSION:
		ep = iscsi_lookup_endpoint(ev->u.c_bound_session.ep_handle);
		if (!ep) {
			err = -EINVAL;
			break;
		}

		err = iscsi_if_create_session(priv, ep, ev,
					portid,
					ev->u.c_bound_session.initial_cmdsn,
					ev->u.c_bound_session.cmds_max,
					ev->u.c_bound_session.queue_depth);
		break;
	case ISCSI_UEVENT_DESTROY_SESSION:
		session = iscsi_session_lookup(ev->u.d_session.sid);
		if (session)
			transport->destroy_session(session);
		else
			err = -EINVAL;
		break;
	case ISCSI_UEVENT_UNBIND_SESSION:
		session = iscsi_session_lookup(ev->u.d_session.sid);
		if (session)
			scsi_queue_work(iscsi_session_to_shost(session),
					&session->unbind_work);
		else
			err = -EINVAL;
		break;
	case ISCSI_UEVENT_CREATE_CONN:
		err = iscsi_if_create_conn(transport, ev);
		break;
	case ISCSI_UEVENT_DESTROY_CONN:
		err = iscsi_if_destroy_conn(transport, ev);
		break;
	case ISCSI_UEVENT_BIND_CONN:
		session = iscsi_session_lookup(ev->u.b_conn.sid);
		conn = iscsi_conn_lookup(ev->u.b_conn.sid, ev->u.b_conn.cid);

		if (conn && conn->ep)
			iscsi_if_ep_disconnect(transport, conn->ep->id);

		if (!session || !conn) {
			err = -EINVAL;
			break;
		}

		ev->r.retcode =	transport->bind_conn(session, conn,
						ev->u.b_conn.transport_eph,
						ev->u.b_conn.is_leading);
		if (ev->r.retcode || !transport->ep_connect)
			break;

		ep = iscsi_lookup_endpoint(ev->u.b_conn.transport_eph);
		if (ep) {
			ep->conn = conn;

			mutex_lock(&conn->ep_mutex);
			conn->ep = ep;
			mutex_unlock(&conn->ep_mutex);
		} else
			iscsi_cls_conn_printk(KERN_ERR, conn,
					      "Could not set ep conn "
					      "binding\n");
		break;
	case ISCSI_UEVENT_SET_PARAM:
		err = iscsi_set_param(transport, ev);
		break;
	case ISCSI_UEVENT_START_CONN:
		conn = iscsi_conn_lookup(ev->u.start_conn.sid, ev->u.start_conn.cid);
		if (conn)
			ev->r.retcode = transport->start_conn(conn);
		else
			err = -EINVAL;
		break;
	case ISCSI_UEVENT_STOP_CONN:
		conn = iscsi_conn_lookup(ev->u.stop_conn.sid, ev->u.stop_conn.cid);
		if (conn)
			transport->stop_conn(conn, ev->u.stop_conn.flag);
		else
			err = -EINVAL;
		break;
	case ISCSI_UEVENT_SEND_PDU:
		conn = iscsi_conn_lookup(ev->u.send_pdu.sid, ev->u.send_pdu.cid);
		if (conn)
			ev->r.retcode =	transport->send_pdu(conn,
				(struct iscsi_hdr*)((char*)ev + sizeof(*ev)),
				(char*)ev + sizeof(*ev) + ev->u.send_pdu.hdr_size,
				ev->u.send_pdu.data_size);
		else
			err = -EINVAL;
		break;
	case ISCSI_UEVENT_GET_STATS:
		err = iscsi_if_get_stats(transport, nlh);
		break;
	case ISCSI_UEVENT_TRANSPORT_EP_CONNECT:
	case ISCSI_UEVENT_TRANSPORT_EP_POLL:
	case ISCSI_UEVENT_TRANSPORT_EP_DISCONNECT:
	case ISCSI_UEVENT_TRANSPORT_EP_CONNECT_THROUGH_HOST:
		err = iscsi_if_transport_ep(transport, ev, nlh->nlmsg_type);
		break;
	case ISCSI_UEVENT_TGT_DSCVR:
		err = iscsi_tgt_dscvr(transport, ev);
		break;
	case ISCSI_UEVENT_SET_HOST_PARAM:
		err = iscsi_set_host_param(transport, ev);
		break;
	case ISCSI_UEVENT_PATH_UPDATE:
		err = iscsi_set_path(transport, ev);
		break;
	case ISCSI_UEVENT_SET_IFACE_PARAMS:
		err = iscsi_set_iface_params(transport, ev,
					     nlmsg_attrlen(nlh, sizeof(*ev)));
		break;
	case ISCSI_UEVENT_PING:
		err = iscsi_send_ping(transport, ev);
		break;
	case ISCSI_UEVENT_GET_CHAP:
		err = iscsi_get_chap(transport, nlh);
		break;
	case ISCSI_UEVENT_DELETE_CHAP:
		err = iscsi_delete_chap(transport, ev);
		break;
	case ISCSI_UEVENT_SET_FLASHNODE_PARAMS:
		err = iscsi_set_flashnode_param(transport, ev,
						nlmsg_attrlen(nlh,
							      sizeof(*ev)));
		break;
	case ISCSI_UEVENT_NEW_FLASHNODE:
		err = iscsi_new_flashnode(transport, ev,
					  nlmsg_attrlen(nlh, sizeof(*ev)));
		break;
	case ISCSI_UEVENT_DEL_FLASHNODE:
		err = iscsi_del_flashnode(transport, ev);
		break;
	case ISCSI_UEVENT_LOGIN_FLASHNODE:
		err = iscsi_login_flashnode(transport, ev);
		break;
	case ISCSI_UEVENT_LOGOUT_FLASHNODE:
		err = iscsi_logout_flashnode(transport, ev);
		break;
	case ISCSI_UEVENT_LOGOUT_FLASHNODE_SID:
		err = iscsi_logout_flashnode_sid(transport, ev);
		break;
	case ISCSI_UEVENT_SET_CHAP:
		err = iscsi_set_chap(transport, ev,
				     nlmsg_attrlen(nlh, sizeof(*ev)));
		break;
	case ISCSI_UEVENT_GET_HOST_STATS:
		err = iscsi_get_host_stats(transport, nlh);
		break;
	default:
		err = -ENOSYS;
		break;
	}

	module_put(transport->owner);
	return err;
}