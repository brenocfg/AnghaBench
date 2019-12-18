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
struct rdma_ah_attr {int /*<<< orphan*/  port_num; int /*<<< orphan*/  type; } ;
struct ib_port_attr {int /*<<< orphan*/  subnet_prefix; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  OPA_DEFAULT_GID_PREFIX ; 
 int /*<<< orphan*/  OPA_MAKE_ID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RDMA_AH_ATTR_TYPE_IB ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 scalar_t__ ib_query_port (struct ib_device*,int /*<<< orphan*/ ,struct ib_port_attr*) ; 
 int /*<<< orphan*/  rdma_ah_get_dlid (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_ah_set_grh (struct rdma_ah_attr*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_interface_id (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_subnet_prefix (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rdma_ah_conv_opa_to_ib(struct ib_device *dev,
				  struct rdma_ah_attr *ib,
				  struct rdma_ah_attr *opa)
{
	struct ib_port_attr port_attr;
	int ret = 0;

	/* Do structure copy and the over-write fields */
	*ib = *opa;

	ib->type = RDMA_AH_ATTR_TYPE_IB;
	rdma_ah_set_grh(ib, NULL, 0, 0, 1, 0);

	if (ib_query_port(dev, opa->port_num, &port_attr)) {
		/* Set to default subnet to indicate error */
		rdma_ah_set_subnet_prefix(ib, OPA_DEFAULT_GID_PREFIX);
		ret = -EINVAL;
	} else {
		rdma_ah_set_subnet_prefix(ib,
					  cpu_to_be64(port_attr.subnet_prefix));
	}
	rdma_ah_set_interface_id(ib, OPA_MAKE_ID(rdma_ah_get_dlid(opa)));
	return ret;
}