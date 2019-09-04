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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct nfp_app {int dummy; } ;
typedef  enum nfp_repr_type { ____Placeholder_nfp_repr_type } nfp_repr_type ;

/* Variables and functions */
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_PORT_PHYS_PORT_NUM ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_PORT_TYPE ; 
#define  NFP_FLOWER_CMSG_PORT_TYPE_PCIE_PORT 129 
#define  NFP_FLOWER_CMSG_PORT_TYPE_PHYS_PORT 128 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_PORT_VNIC ; 
 int /*<<< orphan*/  NFP_FLOWER_CMSG_PORT_VNIC_TYPE ; 
 int NFP_FLOWER_CMSG_PORT_VNIC_TYPE_PF ; 
 int NFP_REPR_TYPE_PF ; 
 int NFP_REPR_TYPE_PHYS_PORT ; 
 int NFP_REPR_TYPE_VF ; 
 int __NFP_REPR_TYPE_MAX ; 

__attribute__((used)) static enum nfp_repr_type
nfp_flower_repr_get_type_and_port(struct nfp_app *app, u32 port_id, u8 *port)
{
	switch (FIELD_GET(NFP_FLOWER_CMSG_PORT_TYPE, port_id)) {
	case NFP_FLOWER_CMSG_PORT_TYPE_PHYS_PORT:
		*port = FIELD_GET(NFP_FLOWER_CMSG_PORT_PHYS_PORT_NUM,
				  port_id);
		return NFP_REPR_TYPE_PHYS_PORT;

	case NFP_FLOWER_CMSG_PORT_TYPE_PCIE_PORT:
		*port = FIELD_GET(NFP_FLOWER_CMSG_PORT_VNIC, port_id);
		if (FIELD_GET(NFP_FLOWER_CMSG_PORT_VNIC_TYPE, port_id) ==
		    NFP_FLOWER_CMSG_PORT_VNIC_TYPE_PF)
			return NFP_REPR_TYPE_PF;
		else
			return NFP_REPR_TYPE_VF;
	}

	return __NFP_REPR_TYPE_MAX;
}