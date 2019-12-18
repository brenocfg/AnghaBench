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
typedef  size_t u8 ;
struct rdma_ah_attr {int dummy; } ;
struct ib_device {int dummy; } ;
struct hfi1_pportdata {int dummy; } ;
struct hfi1_ibport {size_t* sl_to_sc; } ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (size_t*) ; 
 int EINVAL ; 
 int IB_AH_GRH ; 
 size_t array_index_nospec (size_t,size_t) ; 
 struct hfi1_devdata* dd_from_ppd (struct hfi1_pportdata*) ; 
 scalar_t__ hfi1_check_mcast (int /*<<< orphan*/ ) ; 
 int num_vls ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 
 int rdma_ah_get_ah_flags (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_ah_get_dlid (struct rdma_ah_attr*) ; 
 int /*<<< orphan*/  rdma_ah_get_port_num (struct rdma_ah_attr*) ; 
 size_t rdma_ah_get_sl (struct rdma_ah_attr*) ; 
 int sc_to_vlt (struct hfi1_devdata*,size_t) ; 
 struct hfi1_ibport* to_iport (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int hfi1_check_ah(struct ib_device *ibdev, struct rdma_ah_attr *ah_attr)
{
	struct hfi1_ibport *ibp;
	struct hfi1_pportdata *ppd;
	struct hfi1_devdata *dd;
	u8 sc5;
	u8 sl;

	if (hfi1_check_mcast(rdma_ah_get_dlid(ah_attr)) &&
	    !(rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH))
		return -EINVAL;

	/* test the mapping for validity */
	ibp = to_iport(ibdev, rdma_ah_get_port_num(ah_attr));
	ppd = ppd_from_ibp(ibp);
	dd = dd_from_ppd(ppd);

	sl = rdma_ah_get_sl(ah_attr);
	if (sl >= ARRAY_SIZE(ibp->sl_to_sc))
		return -EINVAL;
	sl = array_index_nospec(sl, ARRAY_SIZE(ibp->sl_to_sc));

	sc5 = ibp->sl_to_sc[sl];
	if (sc_to_vlt(dd, sc5) > num_vls && sc_to_vlt(dd, sc5) != 0xf)
		return -EINVAL;
	return 0;
}