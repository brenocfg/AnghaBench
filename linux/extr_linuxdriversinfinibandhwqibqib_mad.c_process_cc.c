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
typedef  int /*<<< orphan*/  u8 ;
struct qib_ibport {int dummy; } ;
struct ib_smp {int dummy; } ;
struct ib_mad {int dummy; } ;
struct ib_device {int dummy; } ;
struct ib_cc_mad {int class_version; int method; int /*<<< orphan*/  status; int /*<<< orphan*/  attr_id; } ;

/* Variables and functions */
#define  IB_CC_ATTR_CA_CONGESTION_SETTING 135 
#define  IB_CC_ATTR_CLASSPORTINFO 134 
#define  IB_CC_ATTR_CONGESTION_CONTROL_TABLE 133 
#define  IB_CC_ATTR_CONGESTION_INFO 132 
 int IB_MAD_RESULT_SUCCESS ; 
#define  IB_MGMT_METHOD_GET 131 
#define  IB_MGMT_METHOD_GET_RESP 130 
#define  IB_MGMT_METHOD_SET 129 
#define  IB_MGMT_METHOD_TRAP 128 
 int /*<<< orphan*/  IB_SMP_UNSUP_METHOD ; 
 int /*<<< orphan*/  IB_SMP_UNSUP_METH_ATTR ; 
 int /*<<< orphan*/  IB_SMP_UNSUP_VERSION ; 
 int cc_get_classportinfo (struct ib_cc_mad*,struct ib_device*) ; 
 int cc_get_congestion_control_table (struct ib_cc_mad*,struct ib_device*,int /*<<< orphan*/ ) ; 
 int cc_get_congestion_info (struct ib_cc_mad*,struct ib_device*,int /*<<< orphan*/ ) ; 
 int cc_get_congestion_setting (struct ib_cc_mad*,struct ib_device*,int /*<<< orphan*/ ) ; 
 int cc_set_congestion_control_table (struct ib_cc_mad*,struct ib_device*,int /*<<< orphan*/ ) ; 
 int cc_set_congestion_setting (struct ib_cc_mad*,struct ib_device*,int /*<<< orphan*/ ) ; 
 int check_cc_key (struct qib_ibport*,struct ib_cc_mad*,int) ; 
 int reply (struct ib_smp*) ; 
 struct qib_ibport* to_iport (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int process_cc(struct ib_device *ibdev, int mad_flags,
			u8 port, const struct ib_mad *in_mad,
			struct ib_mad *out_mad)
{
	struct ib_cc_mad *ccp = (struct ib_cc_mad *)out_mad;
	struct qib_ibport *ibp = to_iport(ibdev, port);
	int ret;

	*out_mad = *in_mad;

	if (ccp->class_version != 2) {
		ccp->status |= IB_SMP_UNSUP_VERSION;
		ret = reply((struct ib_smp *)ccp);
		goto bail;
	}

	ret = check_cc_key(ibp, ccp, mad_flags);
	if (ret)
		goto bail;

	switch (ccp->method) {
	case IB_MGMT_METHOD_GET:
		switch (ccp->attr_id) {
		case IB_CC_ATTR_CLASSPORTINFO:
			ret = cc_get_classportinfo(ccp, ibdev);
			goto bail;

		case IB_CC_ATTR_CONGESTION_INFO:
			ret = cc_get_congestion_info(ccp, ibdev, port);
			goto bail;

		case IB_CC_ATTR_CA_CONGESTION_SETTING:
			ret = cc_get_congestion_setting(ccp, ibdev, port);
			goto bail;

		case IB_CC_ATTR_CONGESTION_CONTROL_TABLE:
			ret = cc_get_congestion_control_table(ccp, ibdev, port);
			goto bail;

			/* FALLTHROUGH */
		default:
			ccp->status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply((struct ib_smp *) ccp);
			goto bail;
		}

	case IB_MGMT_METHOD_SET:
		switch (ccp->attr_id) {
		case IB_CC_ATTR_CA_CONGESTION_SETTING:
			ret = cc_set_congestion_setting(ccp, ibdev, port);
			goto bail;

		case IB_CC_ATTR_CONGESTION_CONTROL_TABLE:
			ret = cc_set_congestion_control_table(ccp, ibdev, port);
			goto bail;

			/* FALLTHROUGH */
		default:
			ccp->status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply((struct ib_smp *) ccp);
			goto bail;
		}

	case IB_MGMT_METHOD_GET_RESP:
		/*
		 * The ib_mad module will call us to process responses
		 * before checking for other consumers.
		 * Just tell the caller to process it normally.
		 */
		ret = IB_MAD_RESULT_SUCCESS;
		goto bail;

	case IB_MGMT_METHOD_TRAP:
	default:
		ccp->status |= IB_SMP_UNSUP_METHOD;
		ret = reply((struct ib_smp *) ccp);
	}

bail:
	return ret;
}