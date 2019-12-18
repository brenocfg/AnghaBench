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
typedef  union ib_gid {int dummy; } ib_gid ;
typedef  int /*<<< orphan*/  u8 ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct resolve_cb_context {int status; int /*<<< orphan*/  comp; } ;
struct rdma_dev_addr {int hoplimit; int /*<<< orphan*/  dst_dev_addr; struct ib_gid_attr const* sgid_attr; int /*<<< orphan*/ * net; } ;
struct ib_gid_attr {int dummy; } ;
typedef  int /*<<< orphan*/  dev_addr ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rdma_dev_addr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_gid2ip (struct sockaddr*,union ib_gid const*) ; 
 int rdma_resolve_ip (struct sockaddr*,struct sockaddr*,struct rdma_dev_addr*,int,int /*<<< orphan*/ ,int,struct resolve_cb_context*) ; 
 int /*<<< orphan*/  resolve_cb ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

int rdma_addr_find_l2_eth_by_grh(const union ib_gid *sgid,
				 const union ib_gid *dgid,
				 u8 *dmac, const struct ib_gid_attr *sgid_attr,
				 int *hoplimit)
{
	struct rdma_dev_addr dev_addr;
	struct resolve_cb_context ctx;
	union {
		struct sockaddr_in  _sockaddr_in;
		struct sockaddr_in6 _sockaddr_in6;
	} sgid_addr, dgid_addr;
	int ret;

	rdma_gid2ip((struct sockaddr *)&sgid_addr, sgid);
	rdma_gid2ip((struct sockaddr *)&dgid_addr, dgid);

	memset(&dev_addr, 0, sizeof(dev_addr));
	dev_addr.net = &init_net;
	dev_addr.sgid_attr = sgid_attr;

	init_completion(&ctx.comp);
	ret = rdma_resolve_ip((struct sockaddr *)&sgid_addr,
			      (struct sockaddr *)&dgid_addr, &dev_addr, 1000,
			      resolve_cb, true, &ctx);
	if (ret)
		return ret;

	wait_for_completion(&ctx.comp);

	ret = ctx.status;
	if (ret)
		return ret;

	memcpy(dmac, dev_addr.dst_dev_addr, ETH_ALEN);
	*hoplimit = dev_addr.hoplimit;
	return 0;
}