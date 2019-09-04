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
struct TYPE_2__ {int class_version; int method; int /*<<< orphan*/  status; int /*<<< orphan*/  attr_id; } ;
struct ib_pma_mad {TYPE_1__ mad_hdr; int /*<<< orphan*/  data; } ;
struct ib_mad_hdr {int dummy; } ;
struct ib_mad {int dummy; } ;
struct ib_device {int dummy; } ;
struct ib_class_port_info {int /*<<< orphan*/  capability_mask; } ;

/* Variables and functions */
 int IB_MAD_RESULT_FAILURE ; 
 int IB_MAD_RESULT_SUCCESS ; 
#define  IB_MGMT_METHOD_GET 134 
#define  IB_MGMT_METHOD_GET_RESP 133 
#define  IB_MGMT_METHOD_SET 132 
#define  IB_MGMT_METHOD_TRAP 131 
 int /*<<< orphan*/  IB_PMA_CLASS_CAP_EXT_WIDTH ; 
#define  IB_PMA_CLASS_PORT_INFO 130 
#define  IB_PMA_PORT_COUNTERS 129 
#define  IB_PMA_PORT_COUNTERS_EXT 128 
 int /*<<< orphan*/  IB_SMP_UNSUP_METHOD ; 
 int /*<<< orphan*/  IB_SMP_UNSUP_METH_ATTR ; 
 int /*<<< orphan*/  IB_SMP_UNSUP_VERSION ; 
 int pma_get_ib_portcounters (struct ib_pma_mad*,struct ib_device*,int /*<<< orphan*/ ) ; 
 int pma_get_ib_portcounters_ext (struct ib_pma_mad*,struct ib_device*,int /*<<< orphan*/ ) ; 
 int reply (struct ib_mad_hdr*) ; 

__attribute__((used)) static int process_perf(struct ib_device *ibdev, u8 port,
			const struct ib_mad *in_mad,
			struct ib_mad *out_mad)
{
	struct ib_pma_mad *pmp = (struct ib_pma_mad *)out_mad;
	struct ib_class_port_info *cpi = (struct ib_class_port_info *)
						&pmp->data;
	int ret = IB_MAD_RESULT_FAILURE;

	*out_mad = *in_mad;
	if (pmp->mad_hdr.class_version != 1) {
		pmp->mad_hdr.status |= IB_SMP_UNSUP_VERSION;
		ret = reply((struct ib_mad_hdr *)pmp);
		return ret;
	}

	switch (pmp->mad_hdr.method) {
	case IB_MGMT_METHOD_GET:
		switch (pmp->mad_hdr.attr_id) {
		case IB_PMA_PORT_COUNTERS:
			ret = pma_get_ib_portcounters(pmp, ibdev, port);
			break;
		case IB_PMA_PORT_COUNTERS_EXT:
			ret = pma_get_ib_portcounters_ext(pmp, ibdev, port);
			break;
		case IB_PMA_CLASS_PORT_INFO:
			cpi->capability_mask = IB_PMA_CLASS_CAP_EXT_WIDTH;
			ret = reply((struct ib_mad_hdr *)pmp);
			break;
		default:
			pmp->mad_hdr.status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply((struct ib_mad_hdr *)pmp);
			break;
		}
		break;

	case IB_MGMT_METHOD_SET:
		if (pmp->mad_hdr.attr_id) {
			pmp->mad_hdr.status |= IB_SMP_UNSUP_METH_ATTR;
			ret = reply((struct ib_mad_hdr *)pmp);
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