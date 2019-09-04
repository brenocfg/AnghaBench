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
struct ib_device {int dummy; } ;

/* Variables and functions */
 int __mlx4_ib_query_gid (struct ib_device*,int /*<<< orphan*/ ,int,union ib_gid*,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_protocol_ib (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mlx4_ib_query_gid(struct ib_device *ibdev, u8 port, int index,
			     union ib_gid *gid)
{
	if (rdma_protocol_ib(ibdev, port))
		return __mlx4_ib_query_gid(ibdev, port, index, gid, 0);
	return 0;
}