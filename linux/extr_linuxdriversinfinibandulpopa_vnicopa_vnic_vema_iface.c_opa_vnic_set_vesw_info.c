#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct __opa_vesw_info {int /*<<< orphan*/  rsvd4; void* eth_mtu; int /*<<< orphan*/  rsvd3; void* rc; void** u_ucast_dlid; void* u_mcast_dlid; int /*<<< orphan*/  rsvd2; void* pkey; int /*<<< orphan*/  rsvd1; void* def_port_mask; int /*<<< orphan*/  rsvd0; void* vesw_id; void* fabric_id; } ;
struct TYPE_2__ {struct __opa_vesw_info vesw; } ;
struct opa_vnic_adapter {TYPE_1__ info; } ;
struct opa_vesw_info {int /*<<< orphan*/  rsvd4; int /*<<< orphan*/  eth_mtu; int /*<<< orphan*/  rsvd3; int /*<<< orphan*/  rc; int /*<<< orphan*/ * u_ucast_dlid; int /*<<< orphan*/  u_mcast_dlid; int /*<<< orphan*/  rsvd2; int /*<<< orphan*/  pkey; int /*<<< orphan*/  rsvd1; int /*<<< orphan*/  def_port_mask; int /*<<< orphan*/  rsvd0; int /*<<< orphan*/  vesw_id; int /*<<< orphan*/  fabric_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int OPA_VESW_MAX_NUM_DEF_PORT ; 
 void* be16_to_cpu (int /*<<< orphan*/ ) ; 
 void* be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void opa_vnic_set_vesw_info(struct opa_vnic_adapter *adapter,
			    struct opa_vesw_info *info)
{
	struct __opa_vesw_info *dst = &adapter->info.vesw;
	int i;

	dst->fabric_id = be16_to_cpu(info->fabric_id);
	dst->vesw_id = be16_to_cpu(info->vesw_id);
	memcpy(dst->rsvd0, info->rsvd0, ARRAY_SIZE(info->rsvd0));
	dst->def_port_mask = be16_to_cpu(info->def_port_mask);
	memcpy(dst->rsvd1, info->rsvd1, ARRAY_SIZE(info->rsvd1));
	dst->pkey = be16_to_cpu(info->pkey);

	memcpy(dst->rsvd2, info->rsvd2, ARRAY_SIZE(info->rsvd2));
	dst->u_mcast_dlid = be32_to_cpu(info->u_mcast_dlid);
	for (i = 0; i < OPA_VESW_MAX_NUM_DEF_PORT; i++)
		dst->u_ucast_dlid[i] = be32_to_cpu(info->u_ucast_dlid[i]);

	dst->rc = be32_to_cpu(info->rc);

	memcpy(dst->rsvd3, info->rsvd3, ARRAY_SIZE(info->rsvd3));
	dst->eth_mtu = be16_to_cpu(info->eth_mtu);
	memcpy(dst->rsvd4, info->rsvd4, ARRAY_SIZE(info->rsvd4));
}