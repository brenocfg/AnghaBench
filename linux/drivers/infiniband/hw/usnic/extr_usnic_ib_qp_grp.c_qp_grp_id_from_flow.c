#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  sock; } ;
struct TYPE_3__ {int /*<<< orphan*/  port_num; } ;
struct usnic_ib_qp_grp_flow {int trans_type; TYPE_2__ udp; TYPE_1__ usnic_roce; } ;
typedef  enum usnic_transport_type { ____Placeholder_usnic_transport_type } usnic_transport_type ;

/* Variables and functions */
 int EINVAL ; 
#define  USNIC_TRANSPORT_IPV4_UDP 129 
#define  USNIC_TRANSPORT_ROCE_CUSTOM 128 
 int /*<<< orphan*/  usnic_err (char*,int) ; 
 int usnic_transport_sock_get_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qp_grp_id_from_flow(struct usnic_ib_qp_grp_flow *qp_flow,
				uint32_t *id)
{
	enum usnic_transport_type trans_type = qp_flow->trans_type;
	int err;
	uint16_t port_num = 0;

	switch (trans_type) {
	case USNIC_TRANSPORT_ROCE_CUSTOM:
		*id = qp_flow->usnic_roce.port_num;
		break;
	case USNIC_TRANSPORT_IPV4_UDP:
		err = usnic_transport_sock_get_addr(qp_flow->udp.sock,
							NULL, NULL,
							&port_num);
		if (err)
			return err;
		/*
		 * Copy port_num to stack first and then to *id,
		 * so that the short to int cast works for little
		 * and big endian systems.
		 */
		*id = port_num;
		break;
	default:
		usnic_err("Unsupported transport %u\n", trans_type);
		return -EINVAL;
	}

	return 0;
}