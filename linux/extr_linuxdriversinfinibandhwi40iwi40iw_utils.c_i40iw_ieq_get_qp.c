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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct tcphdr {int /*<<< orphan*/  source; int /*<<< orphan*/  dest; } ;
struct TYPE_7__ {int /*<<< orphan*/  u6_addr32; } ;
struct TYPE_8__ {TYPE_3__ in6_u; } ;
struct TYPE_5__ {int /*<<< orphan*/  u6_addr32; } ;
struct TYPE_6__ {TYPE_1__ in6_u; } ;
struct ipv6hdr {TYPE_4__ saddr; TYPE_2__ daddr; } ;
struct iphdr {int version; int /*<<< orphan*/  saddr; int /*<<< orphan*/  daddr; } ;
struct i40iw_sc_qp {int dummy; } ;
struct i40iw_sc_dev {scalar_t__ back_dev; } ;
struct i40iw_qp {struct i40iw_sc_qp sc_qp; } ;
struct i40iw_puda_buf {scalar_t__ iph; scalar_t__ tcph; } ;
struct i40iw_device {int /*<<< orphan*/  cm_core; } ;
struct i40iw_cm_node {struct i40iw_qp* iwqp; } ;
typedef  int /*<<< orphan*/  rem_addr ;
typedef  int /*<<< orphan*/  loc_addr ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_copy_ip_ntohl (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct i40iw_cm_node* i40iw_find_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

struct i40iw_sc_qp *i40iw_ieq_get_qp(struct i40iw_sc_dev *dev,
				     struct i40iw_puda_buf *buf)
{
	struct i40iw_device *iwdev = (struct i40iw_device *)dev->back_dev;
	struct i40iw_qp *iwqp;
	struct i40iw_cm_node *cm_node;
	u32 loc_addr[4], rem_addr[4];
	u16 loc_port, rem_port;
	struct ipv6hdr *ip6h;
	struct iphdr *iph = (struct iphdr *)buf->iph;
	struct tcphdr *tcph = (struct tcphdr *)buf->tcph;

	if (iph->version == 4) {
		memset(loc_addr, 0, sizeof(loc_addr));
		loc_addr[0] = ntohl(iph->daddr);
		memset(rem_addr, 0, sizeof(rem_addr));
		rem_addr[0] = ntohl(iph->saddr);
	} else {
		ip6h = (struct ipv6hdr *)buf->iph;
		i40iw_copy_ip_ntohl(loc_addr, ip6h->daddr.in6_u.u6_addr32);
		i40iw_copy_ip_ntohl(rem_addr, ip6h->saddr.in6_u.u6_addr32);
	}
	loc_port = ntohs(tcph->dest);
	rem_port = ntohs(tcph->source);

	cm_node = i40iw_find_node(&iwdev->cm_core, rem_port, rem_addr, loc_port,
				  loc_addr, false, true);
	if (!cm_node)
		return NULL;
	iwqp = cm_node->iwqp;
	return &iwqp->sc_qp;
}