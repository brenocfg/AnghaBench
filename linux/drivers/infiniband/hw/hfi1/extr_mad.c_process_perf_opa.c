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
typedef  int u32 ;
struct TYPE_2__ {scalar_t__ class_version; int method; int /*<<< orphan*/  status; int /*<<< orphan*/  attr_id; } ;
struct opa_pma_mad {TYPE_1__ mad_hdr; } ;
struct opa_mad {int dummy; } ;
struct ib_mad_hdr {int dummy; } ;
struct ib_device {int dummy; } ;

/* Variables and functions */
 int IB_MAD_RESULT_SUCCESS ; 
#define  IB_MGMT_METHOD_GET 137 
#define  IB_MGMT_METHOD_GET_RESP 136 
#define  IB_MGMT_METHOD_SET 135 
#define  IB_MGMT_METHOD_TRAP 134 
#define  IB_PMA_CLASS_PORT_INFO 133 
 int /*<<< orphan*/  IB_SMP_UNSUP_METHOD ; 
 int /*<<< orphan*/  IB_SMP_UNSUP_METH_ATTR ; 
 int /*<<< orphan*/  IB_SMP_UNSUP_VERSION ; 
#define  OPA_PM_ATTRIB_ID_CLEAR_PORT_STATUS 132 
#define  OPA_PM_ATTRIB_ID_DATA_PORT_COUNTERS 131 
#define  OPA_PM_ATTRIB_ID_ERROR_INFO 130 
#define  OPA_PM_ATTRIB_ID_ERROR_PORT_COUNTERS 129 
#define  OPA_PM_ATTRIB_ID_PORT_STATUS 128 
 scalar_t__ OPA_SM_CLASS_VERSION ; 
 int pma_get_opa_classportinfo (struct opa_pma_mad*,struct ib_device*,int*) ; 
 int pma_get_opa_datacounters (struct opa_pma_mad*,struct ib_device*,int /*<<< orphan*/ ,int*) ; 
 int pma_get_opa_errorinfo (struct opa_pma_mad*,struct ib_device*,int /*<<< orphan*/ ,int*) ; 
 int pma_get_opa_porterrors (struct opa_pma_mad*,struct ib_device*,int /*<<< orphan*/ ,int*) ; 
 int pma_get_opa_portstatus (struct opa_pma_mad*,struct ib_device*,int /*<<< orphan*/ ,int*) ; 
 int pma_set_opa_errorinfo (struct opa_pma_mad*,struct ib_device*,int /*<<< orphan*/ ,int*) ; 
 int pma_set_opa_portstatus (struct opa_pma_mad*,struct ib_device*,int /*<<< orphan*/ ,int*) ; 
 int reply (struct ib_mad_hdr*) ; 

__attribute__((used)) static int process_perf_opa(struct ib_device *ibdev, u8 port,
			    const struct opa_mad *in_mad,
			    struct opa_mad *out_mad, u32 *resp_len)
{
	struct opa_pma_mad *pmp = (struct opa_pma_mad *)out_mad;
	int ret;

	*out_mad = *in_mad;

	if (pmp->mad_hdr.class_version != OPA_SM_CLASS_VERSION) {
		pmp->mad_hdr.status |= IB_SMP_UNSUP_VERSION;
		return reply((struct ib_mad_hdr *)pmp);
	}

	*resp_len = sizeof(pmp->mad_hdr);

	switch (pmp->mad_hdr.method) {
	case IB_MGMT_METHOD_GET:
		switch (pmp->mad_hdr.attr_id) {
		case IB_PMA_CLASS_PORT_INFO:
			ret = pma_get_opa_classportinfo(pmp, ibdev, resp_len);
			break;
		case OPA_PM_ATTRIB_ID_PORT_STATUS:
			ret = pma_get_opa_portstatus(pmp, ibdev, port,
						     resp_len);
			break;
		case OPA_PM_ATTRIB_ID_DATA_PORT_COUNTERS:
			ret = pma_get_opa_datacounters(pmp, ibdev, port,
						       resp_len);
			break;
		case OPA_PM_ATTRIB_ID_ERROR_PORT_COUNTERS:
			ret = pma_get_opa_porterrors(pmp, ibdev, port,
						     resp_len);
			break;
		case OPA_PM_ATTRIB_ID_ERROR_INFO:
			ret = pma_get_opa_errorinfo(pmp, ibdev, port,
						    resp_len);
			break;
		default:
			pmp->mad_hdr.status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply((struct ib_mad_hdr *)pmp);
			break;
		}
		break;

	case IB_MGMT_METHOD_SET:
		switch (pmp->mad_hdr.attr_id) {
		case OPA_PM_ATTRIB_ID_CLEAR_PORT_STATUS:
			ret = pma_set_opa_portstatus(pmp, ibdev, port,
						     resp_len);
			break;
		case OPA_PM_ATTRIB_ID_ERROR_INFO:
			ret = pma_set_opa_errorinfo(pmp, ibdev, port,
						    resp_len);
			break;
		default:
			pmp->mad_hdr.status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply((struct ib_mad_hdr *)pmp);
			break;
		}
		break;

	case IB_MGMT_METHOD_TRAP:
	case IB_MGMT_METHOD_GET_RESP:
		/*
		 * The ib_mad module will call us to process responses
		 * before checking for other consumers.
		 * Just tell the caller to process it normally.
		 */
		ret = IB_MAD_RESULT_SUCCESS;
		break;

	default:
		pmp->mad_hdr.status |= IB_SMP_UNSUP_METHOD;
		ret = reply((struct ib_mad_hdr *)pmp);
		break;
	}

	return ret;
}