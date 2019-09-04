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
typedef  int /*<<< orphan*/  u8 ;
struct ib_port_immutable {void* core_cap_flags; int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  pkey_tbl_len; } ;
struct ib_port_attr {int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  pkey_tbl_len; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 void* RDMA_CORE_PORT_RAW_PACKET ; 
 int ib_query_port (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 

__attribute__((used)) static int mlx5_port_rep_immutable(struct ib_device *ibdev, u8 port_num,
				   struct ib_port_immutable *immutable)
{
	struct ib_port_attr attr;
	int err;

	immutable->core_cap_flags = RDMA_CORE_PORT_RAW_PACKET;

	err = ib_query_port(ibdev, port_num, &attr);
	if (err)
		return err;

	immutable->pkey_tbl_len = attr.pkey_tbl_len;
	immutable->gid_tbl_len = attr.gid_tbl_len;
	immutable->core_cap_flags = RDMA_CORE_PORT_RAW_PACKET;

	return 0;
}