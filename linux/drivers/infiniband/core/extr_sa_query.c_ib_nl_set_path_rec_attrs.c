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
typedef  int /*<<< orphan*/  val64 ;
typedef  int /*<<< orphan*/  val16 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {int dummy; } ;
struct sa_path_rec {scalar_t__ reversible; int /*<<< orphan*/  qos_class; int /*<<< orphan*/  pkey; int /*<<< orphan*/  traffic_class; int /*<<< orphan*/  sgid; int /*<<< orphan*/  dgid; int /*<<< orphan*/  service_id; } ;
struct rdma_ls_resolve_header {int /*<<< orphan*/  path_use; int /*<<< orphan*/  port_num; int /*<<< orphan*/  device_name; } ;
struct ib_sa_query {int /*<<< orphan*/  path_use; TYPE_5__* port; TYPE_2__* mad_buf; } ;
struct TYPE_6__ {int comp_mask; } ;
struct ib_sa_mad {TYPE_1__ sa_hdr; } ;
typedef  int ib_sa_comp_mask ;
struct TYPE_10__ {int /*<<< orphan*/  port_num; TYPE_4__* agent; } ;
struct TYPE_9__ {TYPE_3__* device; } ;
struct TYPE_8__ {int /*<<< orphan*/  dev; } ;
struct TYPE_7__ {struct sa_path_rec** context; struct ib_sa_mad* mad; } ;

/* Variables and functions */
 int IB_SA_PATH_REC_DGID ; 
 int IB_SA_PATH_REC_PKEY ; 
 int IB_SA_PATH_REC_QOS_CLASS ; 
 int IB_SA_PATH_REC_REVERSIBLE ; 
 int IB_SA_PATH_REC_SERVICE_ID ; 
 int IB_SA_PATH_REC_SGID ; 
 int IB_SA_PATH_REC_TRAFFIC_CLASS ; 
 int /*<<< orphan*/  LS_DEVICE_NAME_MAX ; 
 int LS_NLA_TYPE_DGID ; 
 int LS_NLA_TYPE_PKEY ; 
 int LS_NLA_TYPE_QOS_CLASS ; 
 int LS_NLA_TYPE_SERVICE_ID ; 
 int LS_NLA_TYPE_SGID ; 
 int LS_NLA_TYPE_TCLASS ; 
 int /*<<< orphan*/  LS_RESOLVE_PATH_USE_GMP ; 
 int /*<<< orphan*/  LS_RESOLVE_PATH_USE_UNIDIRECTIONAL ; 
 int /*<<< orphan*/  NLMSG_ALIGN (int) ; 
 int RDMA_NLA_F_MANDATORY ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_put (struct sk_buff*,int,int,int /*<<< orphan*/ *) ; 
 struct rdma_ls_resolve_header* skb_put (struct sk_buff*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ib_nl_set_path_rec_attrs(struct sk_buff *skb,
				     struct ib_sa_query *query)
{
	struct sa_path_rec *sa_rec = query->mad_buf->context[1];
	struct ib_sa_mad *mad = query->mad_buf->mad;
	ib_sa_comp_mask comp_mask = mad->sa_hdr.comp_mask;
	u16 val16;
	u64 val64;
	struct rdma_ls_resolve_header *header;

	query->mad_buf->context[1] = NULL;

	/* Construct the family header first */
	header = skb_put(skb, NLMSG_ALIGN(sizeof(*header)));
	memcpy(header->device_name, dev_name(&query->port->agent->device->dev),
	       LS_DEVICE_NAME_MAX);
	header->port_num = query->port->port_num;

	if ((comp_mask & IB_SA_PATH_REC_REVERSIBLE) &&
	    sa_rec->reversible != 0)
		query->path_use = LS_RESOLVE_PATH_USE_GMP;
	else
		query->path_use = LS_RESOLVE_PATH_USE_UNIDIRECTIONAL;
	header->path_use = query->path_use;

	/* Now build the attributes */
	if (comp_mask & IB_SA_PATH_REC_SERVICE_ID) {
		val64 = be64_to_cpu(sa_rec->service_id);
		nla_put(skb, RDMA_NLA_F_MANDATORY | LS_NLA_TYPE_SERVICE_ID,
			sizeof(val64), &val64);
	}
	if (comp_mask & IB_SA_PATH_REC_DGID)
		nla_put(skb, RDMA_NLA_F_MANDATORY | LS_NLA_TYPE_DGID,
			sizeof(sa_rec->dgid), &sa_rec->dgid);
	if (comp_mask & IB_SA_PATH_REC_SGID)
		nla_put(skb, RDMA_NLA_F_MANDATORY | LS_NLA_TYPE_SGID,
			sizeof(sa_rec->sgid), &sa_rec->sgid);
	if (comp_mask & IB_SA_PATH_REC_TRAFFIC_CLASS)
		nla_put(skb, RDMA_NLA_F_MANDATORY | LS_NLA_TYPE_TCLASS,
			sizeof(sa_rec->traffic_class), &sa_rec->traffic_class);

	if (comp_mask & IB_SA_PATH_REC_PKEY) {
		val16 = be16_to_cpu(sa_rec->pkey);
		nla_put(skb, RDMA_NLA_F_MANDATORY | LS_NLA_TYPE_PKEY,
			sizeof(val16), &val16);
	}
	if (comp_mask & IB_SA_PATH_REC_QOS_CLASS) {
		val16 = be16_to_cpu(sa_rec->qos_class);
		nla_put(skb, RDMA_NLA_F_MANDATORY | LS_NLA_TYPE_QOS_CLASS,
			sizeof(val16), &val16);
	}
}