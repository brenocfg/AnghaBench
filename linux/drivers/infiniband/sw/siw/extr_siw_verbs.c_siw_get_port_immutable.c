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
struct ib_port_immutable {int /*<<< orphan*/  core_cap_flags; int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  pkey_tbl_len; } ;
struct ib_port_attr {int /*<<< orphan*/  gid_tbl_len; int /*<<< orphan*/  pkey_tbl_len; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  RDMA_CORE_PORT_IWARP ; 
 int siw_query_port (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 

int siw_get_port_immutable(struct ib_device *base_dev, u8 port,
			   struct ib_port_immutable *port_immutable)
{
	struct ib_port_attr attr;
	int rv = siw_query_port(base_dev, port, &attr);

	if (rv)
		return rv;

	port_immutable->pkey_tbl_len = attr.pkey_tbl_len;
	port_immutable->gid_tbl_len = attr.gid_tbl_len;
	port_immutable->core_cap_flags = RDMA_CORE_PORT_IWARP;

	return 0;
}