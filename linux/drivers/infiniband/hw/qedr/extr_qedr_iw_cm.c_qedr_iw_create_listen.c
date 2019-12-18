#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/ * u6_addr32; } ;
struct TYPE_8__ {TYPE_2__ in6_u; } ;
struct sockaddr_in6 {int /*<<< orphan*/  sin6_port; TYPE_3__ sin6_addr; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; } ;
struct qedr_iw_listener {int backlog; int /*<<< orphan*/  qed_handle; struct iw_cm_id* cm_id; struct qedr_dev* dev; } ;
struct qedr_dev {int /*<<< orphan*/  rdma_ctx; TYPE_4__* ops; } ;
struct qed_iwarp_listen_out {int /*<<< orphan*/  handle; } ;
struct qed_iwarp_listen_in {int max_backlog; void** ip_addr; int /*<<< orphan*/  vlan; void* port; int /*<<< orphan*/  ip_version; int /*<<< orphan*/  event_cb; struct qedr_iw_listener* cb_context; } ;
struct TYPE_10__ {scalar_t__ ss_family; } ;
struct iw_cm_id {int /*<<< orphan*/  (* rem_ref ) (struct iw_cm_id*) ;struct qedr_iw_listener* provider_data; TYPE_5__ local_addr; int /*<<< orphan*/  (* add_ref ) (struct iw_cm_id*) ;int /*<<< orphan*/  m_local_addr; int /*<<< orphan*/  device; } ;
struct TYPE_9__ {int (* iwarp_create_listen ) (int /*<<< orphan*/ ,struct qed_iwarp_listen_in*,struct qed_iwarp_listen_out*) ;} ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int /*<<< orphan*/  CONFIG_IPV6 ; 
 int /*<<< orphan*/  DP_DEBUG (struct qedr_dev*,int /*<<< orphan*/ ,char*,TYPE_5__*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  QEDR_MSG_IWARP ; 
 int /*<<< orphan*/  QED_TCP_IPV4 ; 
 int /*<<< orphan*/  QED_TCP_IPV6 ; 
 struct qedr_dev* get_qedr_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct qedr_iw_listener*) ; 
 struct qedr_iw_listener* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void**,int /*<<< orphan*/ ,int) ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qedr_iw_event_handler ; 
 int /*<<< orphan*/  qedr_iw_get_vlan_ipv4 (struct qedr_dev*,void**) ; 
 int /*<<< orphan*/  qedr_iw_get_vlan_ipv6 (void**) ; 
 int /*<<< orphan*/  stub1 (struct iw_cm_id*) ; 
 int stub2 (int /*<<< orphan*/ ,struct qed_iwarp_listen_in*,struct qed_iwarp_listen_out*) ; 
 int /*<<< orphan*/  stub3 (struct iw_cm_id*) ; 

int qedr_iw_create_listen(struct iw_cm_id *cm_id, int backlog)
{
	struct qedr_dev *dev = get_qedr_dev(cm_id->device);
	struct qedr_iw_listener *listener;
	struct qed_iwarp_listen_in iparams;
	struct qed_iwarp_listen_out oparams;
	struct sockaddr_in *laddr;
	struct sockaddr_in6 *laddr6;
	int rc;
	int i;

	laddr = (struct sockaddr_in *)&cm_id->m_local_addr;
	laddr6 = (struct sockaddr_in6 *)&cm_id->m_local_addr;

	DP_DEBUG(dev, QEDR_MSG_IWARP,
		 "Create Listener address: %pISpc\n", &cm_id->local_addr);

	listener = kzalloc(sizeof(*listener), GFP_KERNEL);
	if (!listener)
		return -ENOMEM;

	listener->dev = dev;
	cm_id->add_ref(cm_id);
	listener->cm_id = cm_id;
	listener->backlog = backlog;

	iparams.cb_context = listener;
	iparams.event_cb = qedr_iw_event_handler;
	iparams.max_backlog = backlog;

	if (!IS_ENABLED(CONFIG_IPV6) ||
	    cm_id->local_addr.ss_family == AF_INET) {
		iparams.ip_version = QED_TCP_IPV4;
		memset(iparams.ip_addr, 0, sizeof(iparams.ip_addr));

		iparams.ip_addr[0] = ntohl(laddr->sin_addr.s_addr);
		iparams.port = ntohs(laddr->sin_port);
		iparams.vlan = qedr_iw_get_vlan_ipv4(dev, iparams.ip_addr);
	} else {
		iparams.ip_version = QED_TCP_IPV6;

		for (i = 0; i < 4; i++) {
			iparams.ip_addr[i] =
			    ntohl(laddr6->sin6_addr.in6_u.u6_addr32[i]);
		}

		iparams.port = ntohs(laddr6->sin6_port);

		iparams.vlan = qedr_iw_get_vlan_ipv6(iparams.ip_addr);
	}
	rc = dev->ops->iwarp_create_listen(dev->rdma_ctx, &iparams, &oparams);
	if (rc)
		goto err;

	listener->qed_handle = oparams.handle;
	cm_id->provider_data = listener;
	return rc;

err:
	cm_id->rem_ref(cm_id);
	kfree(listener);
	return rc;
}