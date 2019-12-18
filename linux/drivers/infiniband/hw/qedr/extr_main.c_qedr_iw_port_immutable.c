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
struct ib_port_immutable {int pkey_tbl_len; int gid_tbl_len; scalar_t__ max_mad_size; int /*<<< orphan*/  core_cap_flags; } ;
struct ib_port_attr {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_CORE_PORT_IWARP ; 
 int qedr_query_port (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 

__attribute__((used)) static int qedr_iw_port_immutable(struct ib_device *ibdev, u8 port_num,
				  struct ib_port_immutable *immutable)
{
	struct ib_port_attr attr;
	int err;

	err = qedr_query_port(ibdev, port_num, &attr);
	if (err)
		return err;

	immutable->pkey_tbl_len = 1;
	immutable->gid_tbl_len = 1;
	immutable->core_cap_flags = RDMA_CORE_PORT_IWARP;
	immutable->max_mad_size = 0;

	return 0;
}