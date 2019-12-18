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
typedef  int /*<<< orphan*/  u8 ;
struct sa_path_rec {scalar_t__ hop_limit; int /*<<< orphan*/  rate; int /*<<< orphan*/  sl; } ;
struct TYPE_2__ {int /*<<< orphan*/  dmac; } ;
struct rdma_ah_attr {TYPE_1__ roce; int /*<<< orphan*/  type; } ;
struct ib_gid_attr {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  IB_LID_PERMISSIVE ; 
 scalar_t__ be16_to_cpu (int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int get_src_path_mask (struct ib_device*,int /*<<< orphan*/ ) ; 
 int init_ah_attr_grh_fields (struct ib_device*,int /*<<< orphan*/ ,struct sa_path_rec*,struct rdma_ah_attr*,struct ib_gid_attr const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct rdma_ah_attr*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdma_ah_find_type (struct ib_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ rdma_ah_get_dlid (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_ah_set_dlid (struct rdma_ah_attr*,int) ; 
 int /*<<< orphan*/  rdma_ah_set_make_grd (struct rdma_ah_attr*,int) ; 
 int /*<<< orphan*/  rdma_ah_set_path_bits (struct rdma_ah_attr*,int) ; 
 int /*<<< orphan*/  rdma_ah_set_port_num (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_sl (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdma_ah_set_static_rate (struct rdma_ah_attr*,int /*<<< orphan*/ ) ; 
 int roce_resolve_route_from_path (struct sa_path_rec*,struct ib_gid_attr const*) ; 
 int /*<<< orphan*/  sa_path_get_dlid (struct sa_path_rec*) ; 
 int /*<<< orphan*/  sa_path_get_dmac (struct sa_path_rec*) ; 
 int /*<<< orphan*/  sa_path_get_slid (struct sa_path_rec*) ; 
 scalar_t__ sa_path_is_opa (struct sa_path_rec*) ; 
 scalar_t__ sa_path_is_roce (struct sa_path_rec*) ; 

int ib_init_ah_attr_from_path(struct ib_device *device, u8 port_num,
			      struct sa_path_rec *rec,
			      struct rdma_ah_attr *ah_attr,
			      const struct ib_gid_attr *gid_attr)
{
	int ret = 0;

	memset(ah_attr, 0, sizeof(*ah_attr));
	ah_attr->type = rdma_ah_find_type(device, port_num);
	rdma_ah_set_sl(ah_attr, rec->sl);
	rdma_ah_set_port_num(ah_attr, port_num);
	rdma_ah_set_static_rate(ah_attr, rec->rate);

	if (sa_path_is_roce(rec)) {
		ret = roce_resolve_route_from_path(rec, gid_attr);
		if (ret)
			return ret;

		memcpy(ah_attr->roce.dmac, sa_path_get_dmac(rec), ETH_ALEN);
	} else {
		rdma_ah_set_dlid(ah_attr, be32_to_cpu(sa_path_get_dlid(rec)));
		if (sa_path_is_opa(rec) &&
		    rdma_ah_get_dlid(ah_attr) == be16_to_cpu(IB_LID_PERMISSIVE))
			rdma_ah_set_make_grd(ah_attr, true);

		rdma_ah_set_path_bits(ah_attr,
				      be32_to_cpu(sa_path_get_slid(rec)) &
				      get_src_path_mask(device, port_num));
	}

	if (rec->hop_limit > 0 || sa_path_is_roce(rec))
		ret = init_ah_attr_grh_fields(device, port_num,
					      rec, ah_attr, gid_attr);
	return ret;
}