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
struct sockaddr {int dummy; } ;
struct net_device {int dummy; } ;
struct ib_gid_attr {struct net_device* ndev; } ;
struct ib_device {int dummy; } ;
typedef  int /*<<< orphan*/  gid_attr ;
typedef  enum gid_op_type { ____Placeholder_gid_op_type } gid_op_type ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct ib_gid_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_ip2gid (struct sockaddr*,union ib_gid*) ; 
 int /*<<< orphan*/  update_gid (int,struct ib_device*,int /*<<< orphan*/ ,union ib_gid*,struct ib_gid_attr*) ; 

__attribute__((used)) static void update_gid_ip(enum gid_op_type gid_op,
			  struct ib_device *ib_dev,
			  u8 port, struct net_device *ndev,
			  struct sockaddr *addr)
{
	union ib_gid gid;
	struct ib_gid_attr gid_attr;

	rdma_ip2gid(addr, &gid);
	memset(&gid_attr, 0, sizeof(gid_attr));
	gid_attr.ndev = ndev;

	update_gid(gid_op, ib_dev, port, &gid, &gid_attr);
}