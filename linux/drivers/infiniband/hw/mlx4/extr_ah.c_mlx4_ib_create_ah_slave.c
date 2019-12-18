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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_5__ {int sgid_index; int /*<<< orphan*/ * sgid_attr; } ;
struct rdma_ah_attr {scalar_t__ type; TYPE_1__ grh; } ;
struct TYPE_7__ {int /*<<< orphan*/  vlan; int /*<<< orphan*/  s_mac; } ;
struct TYPE_6__ {int /*<<< orphan*/  port_pd; } ;
struct TYPE_8__ {TYPE_3__ eth; TYPE_2__ ib; } ;
struct mlx4_ib_ah {TYPE_4__ av; } ;
struct ib_ah {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ RDMA_AH_ATTR_TYPE_ROCE ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 int /*<<< orphan*/  cpu_to_be32 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int mlx4_ib_create_ah (struct ib_ah*,struct rdma_ah_attr*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int rdma_ah_get_sl (struct rdma_ah_attr*) ; 
 struct mlx4_ib_ah* to_mah (struct ib_ah*) ; 

int mlx4_ib_create_ah_slave(struct ib_ah *ah, struct rdma_ah_attr *ah_attr,
			    int slave_sgid_index, u8 *s_mac, u16 vlan_tag)
{
	struct rdma_ah_attr slave_attr = *ah_attr;
	struct mlx4_ib_ah *mah = to_mah(ah);
	int ret;

	slave_attr.grh.sgid_attr = NULL;
	slave_attr.grh.sgid_index = slave_sgid_index;
	ret = mlx4_ib_create_ah(ah, &slave_attr, 0, NULL);
	if (ret)
		return ret;

	ah->type = ah_attr->type;

	/* get rid of force-loopback bit */
	mah->av.ib.port_pd &= cpu_to_be32(0x7FFFFFFF);

	if (ah_attr->type == RDMA_AH_ATTR_TYPE_ROCE)
		memcpy(mah->av.eth.s_mac, s_mac, 6);

	if (vlan_tag < 0x1000)
		vlan_tag |= (rdma_ah_get_sl(ah_attr) & 7) << 13;
	mah->av.eth.vlan = cpu_to_be16(vlan_tag);

	return 0;
}