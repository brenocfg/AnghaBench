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
struct ib_wc {int dummy; } ;
struct TYPE_2__ {int mgmt_class; } ;
struct ib_mad {TYPE_1__ mad_hdr; } ;
struct ib_grh {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int IB_MAD_RESULT_SUCCESS ; 
#define  IB_MGMT_CLASS_PERF_MGMT 130 
#define  IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE 129 
#define  IB_MGMT_CLASS_SUBN_LID_ROUTED 128 
 int process_perf (struct ib_device*,int /*<<< orphan*/ ,struct ib_mad const*,struct ib_mad*) ; 
 int process_subn (struct ib_device*,int,int /*<<< orphan*/ ,struct ib_mad const*,struct ib_mad*) ; 

__attribute__((used)) static int hfi1_process_ib_mad(struct ib_device *ibdev, int mad_flags, u8 port,
			       const struct ib_wc *in_wc,
			       const struct ib_grh *in_grh,
			       const struct ib_mad *in_mad,
			       struct ib_mad *out_mad)
{
	int ret;

	switch (in_mad->mad_hdr.mgmt_class) {
	case IB_MGMT_CLASS_SUBN_DIRECTED_ROUTE:
	case IB_MGMT_CLASS_SUBN_LID_ROUTED:
		ret = process_subn(ibdev, mad_flags, port, in_mad, out_mad);
		break;
	case IB_MGMT_CLASS_PERF_MGMT:
		ret = process_perf(ibdev, port, in_mad, out_mad);
		break;
	default:
		ret = IB_MAD_RESULT_SUCCESS;
		break;
	}

	return ret;
}