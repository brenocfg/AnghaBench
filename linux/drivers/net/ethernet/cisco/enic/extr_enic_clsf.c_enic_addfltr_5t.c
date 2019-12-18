#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct TYPE_10__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_8__ {int /*<<< orphan*/  dst; int /*<<< orphan*/  src; } ;
struct TYPE_9__ {TYPE_2__ v4addrs; } ;
struct TYPE_7__ {int ip_proto; } ;
struct flow_keys {TYPE_4__ ports; TYPE_3__ addrs; TYPE_1__ basic; } ;
struct TYPE_11__ {int /*<<< orphan*/  flags; void* dst_port; void* src_port; void* dst_addr; void* src_addr; int /*<<< orphan*/  protocol; } ;
struct TYPE_12__ {TYPE_5__ ipv4; } ;
struct filter {TYPE_6__ u; int /*<<< orphan*/  type; } ;
struct enic {int /*<<< orphan*/  devcmd_lock; int /*<<< orphan*/  vdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLSF_ADD ; 
 int EPROTONOSUPPORT ; 
 int /*<<< orphan*/  FILTER_FIELDS_IPV4_5TUPLE ; 
 int /*<<< orphan*/  FILTER_IPV4_5TUPLE ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  PROTO_TCP ; 
 int /*<<< orphan*/  PROTO_UDP ; 
 void* ntohl (int /*<<< orphan*/ ) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int vnic_dev_classifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,struct filter*) ; 

int enic_addfltr_5t(struct enic *enic, struct flow_keys *keys, u16 rq)
{
	int res;
	struct filter data;

	switch (keys->basic.ip_proto) {
	case IPPROTO_TCP:
		data.u.ipv4.protocol = PROTO_TCP;
		break;
	case IPPROTO_UDP:
		data.u.ipv4.protocol = PROTO_UDP;
		break;
	default:
		return -EPROTONOSUPPORT;
	}

	data.type = FILTER_IPV4_5TUPLE;
	data.u.ipv4.src_addr = ntohl(keys->addrs.v4addrs.src);
	data.u.ipv4.dst_addr = ntohl(keys->addrs.v4addrs.dst);
	data.u.ipv4.src_port = ntohs(keys->ports.src);
	data.u.ipv4.dst_port = ntohs(keys->ports.dst);
	data.u.ipv4.flags = FILTER_FIELDS_IPV4_5TUPLE;

	spin_lock_bh(&enic->devcmd_lock);
	res = vnic_dev_classifier(enic->vdev, CLSF_ADD, &rq, &data);
	spin_unlock_bh(&enic->devcmd_lock);
	res = (res == 0) ? rq : res;

	return res;
}