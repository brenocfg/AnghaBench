#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct i40e_cloud_filter {scalar_t__ n_proto; scalar_t__ tenant_id; int /*<<< orphan*/  vlan_id; int /*<<< orphan*/  dst_ipv4; int /*<<< orphan*/ * dst_ipv6; int /*<<< orphan*/  src_mac; int /*<<< orphan*/  dst_mac; } ;
struct TYPE_5__ {int /*<<< orphan*/  data; } ;
struct TYPE_4__ {int /*<<< orphan*/ * data; } ;
struct TYPE_6__ {TYPE_2__ v4; TYPE_1__ raw_v6; } ;
struct i40e_aqc_cloud_filters_element_data {int /*<<< orphan*/  inner_vlan; TYPE_3__ ipaddr; int /*<<< orphan*/  inner_mac; int /*<<< orphan*/  outer_mac; } ;
typedef  int /*<<< orphan*/  ipa ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ ETH_P_IP ; 
 scalar_t__ ETH_P_IPV6 ; 
 int IPV6_MAX_INDEX ; 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct i40e_aqc_cloud_filters_element_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void
i40e_set_cld_element(struct i40e_cloud_filter *filter,
		     struct i40e_aqc_cloud_filters_element_data *cld)
{
	int i, j;
	u32 ipa;

	memset(cld, 0, sizeof(*cld));
	ether_addr_copy(cld->outer_mac, filter->dst_mac);
	ether_addr_copy(cld->inner_mac, filter->src_mac);

	if (filter->n_proto != ETH_P_IP && filter->n_proto != ETH_P_IPV6)
		return;

	if (filter->n_proto == ETH_P_IPV6) {
#define IPV6_MAX_INDEX	(ARRAY_SIZE(filter->dst_ipv6) - 1)
		for (i = 0, j = 0; i < ARRAY_SIZE(filter->dst_ipv6);
		     i++, j += 2) {
			ipa = be32_to_cpu(filter->dst_ipv6[IPV6_MAX_INDEX - i]);
			ipa = cpu_to_le32(ipa);
			memcpy(&cld->ipaddr.raw_v6.data[j], &ipa, sizeof(ipa));
		}
	} else {
		ipa = be32_to_cpu(filter->dst_ipv4);
		memcpy(&cld->ipaddr.v4.data, &ipa, sizeof(ipa));
	}

	cld->inner_vlan = cpu_to_le16(ntohs(filter->vlan_id));

	/* tenant_id is not supported by FW now, once the support is enabled
	 * fill the cld->tenant_id with cpu_to_le32(filter->tenant_id)
	 */
	if (filter->tenant_id)
		return;
}