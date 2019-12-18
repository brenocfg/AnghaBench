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
typedef  int u32 ;
struct opa_smp {int /*<<< orphan*/  status; int /*<<< orphan*/  attr_mod; } ;
struct ib_mad_hdr {int dummy; } ;
struct ib_device {int dummy; } ;
struct hfi1_pportdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FM_TBL_VL_HIGH_ARB ; 
 int /*<<< orphan*/  FM_TBL_VL_LOW_ARB ; 
 int /*<<< orphan*/  FM_TBL_VL_PREEMPT_ELEMS ; 
 int /*<<< orphan*/  FM_TBL_VL_PREEMPT_MATRIX ; 
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int OPA_AM_NPORT (int) ; 
#define  OPA_VLARB_HIGH_ELEMENTS 131 
#define  OPA_VLARB_LOW_ELEMENTS 130 
#define  OPA_VLARB_PREEMPT_ELEMENTS 129 
#define  OPA_VLARB_PREEMPT_MATRIX 128 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm_get_table (struct hfi1_pportdata*,int /*<<< orphan*/ ,int*) ; 
 struct hfi1_pportdata* ppd_from_ibp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int reply (struct ib_mad_hdr*) ; 
 scalar_t__ smp_length_check (int,int) ; 
 int /*<<< orphan*/  to_iport (struct ib_device*,int) ; 

__attribute__((used)) static int __subn_get_opa_vl_arb(struct opa_smp *smp, u32 am, u8 *data,
				 struct ib_device *ibdev, u8 port,
				 u32 *resp_len, u32 max_len)
{
	struct hfi1_pportdata *ppd = ppd_from_ibp(to_iport(ibdev, port));
	u32 num_ports = OPA_AM_NPORT(am);
	u8 section = (am & 0x00ff0000) >> 16;
	u8 *p = data;
	int size = 256;

	if (num_ports != 1 || smp_length_check(size, max_len)) {
		smp->status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)smp);
	}

	switch (section) {
	case OPA_VLARB_LOW_ELEMENTS:
		fm_get_table(ppd, FM_TBL_VL_LOW_ARB, p);
		break;
	case OPA_VLARB_HIGH_ELEMENTS:
		fm_get_table(ppd, FM_TBL_VL_HIGH_ARB, p);
		break;
	case OPA_VLARB_PREEMPT_ELEMENTS:
		fm_get_table(ppd, FM_TBL_VL_PREEMPT_ELEMS, p);
		break;
	case OPA_VLARB_PREEMPT_MATRIX:
		fm_get_table(ppd, FM_TBL_VL_PREEMPT_MATRIX, p);
		break;
	default:
		pr_warn("OPA SubnGet(VL Arb) AM Invalid : 0x%x\n",
			be32_to_cpu(smp->attr_mod));
		smp->status |= IB_SMP_INVALID_FIELD;
		size = 0;
		break;
	}

	if (size > 0 && resp_len)
		*resp_len += size;

	return reply((struct ib_mad_hdr *)smp);
}