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
typedef  int /*<<< orphan*/  u32 ;
struct opa_smp {int /*<<< orphan*/  status; } ;
struct ib_mad_hdr {int dummy; } ;
struct ib_device {int dummy; } ;
struct TYPE_2__ {int port_cap_flags; } ;
struct hfi1_ibport {TYPE_1__ rvp; } ;
typedef  int __be16 ;

/* Variables and functions */
 int IB_MAD_RESULT_CONSUMED ; 
 int IB_MAD_RESULT_SUCCESS ; 
 int IB_PORT_SM ; 
 int IB_PORT_SM_DISABLED ; 
#define  IB_SMP_ATTR_LED_INFO 145 
#define  IB_SMP_ATTR_NODE_DESC 144 
#define  IB_SMP_ATTR_NODE_INFO 143 
#define  IB_SMP_ATTR_PKEY_TABLE 142 
#define  IB_SMP_ATTR_PORT_INFO 141 
#define  IB_SMP_ATTR_SM_INFO 140 
#define  IB_SMP_ATTR_VL_ARB_TABLE 139 
 int /*<<< orphan*/  IB_SMP_UNSUP_METH_ATTR ; 
#define  OPA_ATTRIB_ID_BUFFER_CONTROL_TABLE 138 
#define  OPA_ATTRIB_ID_CABLE_INFO 137 
#define  OPA_ATTRIB_ID_CONGESTION_CONTROL_TABLE 136 
#define  OPA_ATTRIB_ID_CONGESTION_INFO 135 
#define  OPA_ATTRIB_ID_HFI_CONGESTION_LOG 134 
#define  OPA_ATTRIB_ID_HFI_CONGESTION_SETTING 133 
#define  OPA_ATTRIB_ID_PORT_STATE_INFO 132 
#define  OPA_ATTRIB_ID_SC_TO_SL_MAP 131 
#define  OPA_ATTRIB_ID_SC_TO_VLNT_MAP 130 
#define  OPA_ATTRIB_ID_SC_TO_VLT_MAP 129 
#define  OPA_ATTRIB_ID_SL_TO_SC_MAP 128 
 int __subn_get_opa_bct (struct opa_smp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __subn_get_opa_cable_info (struct opa_smp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __subn_get_opa_cc_table (struct opa_smp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __subn_get_opa_cong_info (struct opa_smp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __subn_get_opa_cong_setting (struct opa_smp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __subn_get_opa_hfi1_cong_log (struct opa_smp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __subn_get_opa_led_info (struct opa_smp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __subn_get_opa_nodedesc (struct opa_smp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __subn_get_opa_nodeinfo (struct opa_smp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __subn_get_opa_pkeytable (struct opa_smp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __subn_get_opa_portinfo (struct opa_smp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __subn_get_opa_psi (struct opa_smp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __subn_get_opa_sc_to_sl (struct opa_smp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __subn_get_opa_sc_to_vlnt (struct opa_smp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __subn_get_opa_sc_to_vlt (struct opa_smp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __subn_get_opa_sl_to_sc (struct opa_smp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int __subn_get_opa_vl_arb (struct opa_smp*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ib_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int reply (struct ib_mad_hdr*) ; 
 struct hfi1_ibport* to_iport (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int subn_get_opa_sma(__be16 attr_id, struct opa_smp *smp, u32 am,
			    u8 *data, struct ib_device *ibdev, u8 port,
			    u32 *resp_len, u32 max_len)
{
	int ret;
	struct hfi1_ibport *ibp = to_iport(ibdev, port);

	switch (attr_id) {
	case IB_SMP_ATTR_NODE_DESC:
		ret = __subn_get_opa_nodedesc(smp, am, data, ibdev, port,
					      resp_len, max_len);
		break;
	case IB_SMP_ATTR_NODE_INFO:
		ret = __subn_get_opa_nodeinfo(smp, am, data, ibdev, port,
					      resp_len, max_len);
		break;
	case IB_SMP_ATTR_PORT_INFO:
		ret = __subn_get_opa_portinfo(smp, am, data, ibdev, port,
					      resp_len, max_len);
		break;
	case IB_SMP_ATTR_PKEY_TABLE:
		ret = __subn_get_opa_pkeytable(smp, am, data, ibdev, port,
					       resp_len, max_len);
		break;
	case OPA_ATTRIB_ID_SL_TO_SC_MAP:
		ret = __subn_get_opa_sl_to_sc(smp, am, data, ibdev, port,
					      resp_len, max_len);
		break;
	case OPA_ATTRIB_ID_SC_TO_SL_MAP:
		ret = __subn_get_opa_sc_to_sl(smp, am, data, ibdev, port,
					      resp_len, max_len);
		break;
	case OPA_ATTRIB_ID_SC_TO_VLT_MAP:
		ret = __subn_get_opa_sc_to_vlt(smp, am, data, ibdev, port,
					       resp_len, max_len);
		break;
	case OPA_ATTRIB_ID_SC_TO_VLNT_MAP:
		ret = __subn_get_opa_sc_to_vlnt(smp, am, data, ibdev, port,
						resp_len, max_len);
		break;
	case OPA_ATTRIB_ID_PORT_STATE_INFO:
		ret = __subn_get_opa_psi(smp, am, data, ibdev, port,
					 resp_len, max_len);
		break;
	case OPA_ATTRIB_ID_BUFFER_CONTROL_TABLE:
		ret = __subn_get_opa_bct(smp, am, data, ibdev, port,
					 resp_len, max_len);
		break;
	case OPA_ATTRIB_ID_CABLE_INFO:
		ret = __subn_get_opa_cable_info(smp, am, data, ibdev, port,
						resp_len, max_len);
		break;
	case IB_SMP_ATTR_VL_ARB_TABLE:
		ret = __subn_get_opa_vl_arb(smp, am, data, ibdev, port,
					    resp_len, max_len);
		break;
	case OPA_ATTRIB_ID_CONGESTION_INFO:
		ret = __subn_get_opa_cong_info(smp, am, data, ibdev, port,
					       resp_len, max_len);
		break;
	case OPA_ATTRIB_ID_HFI_CONGESTION_SETTING:
		ret = __subn_get_opa_cong_setting(smp, am, data, ibdev,
						  port, resp_len, max_len);
		break;
	case OPA_ATTRIB_ID_HFI_CONGESTION_LOG:
		ret = __subn_get_opa_hfi1_cong_log(smp, am, data, ibdev,
						   port, resp_len, max_len);
		break;
	case OPA_ATTRIB_ID_CONGESTION_CONTROL_TABLE:
		ret = __subn_get_opa_cc_table(smp, am, data, ibdev, port,
					      resp_len, max_len);
		break;
	case IB_SMP_ATTR_LED_INFO:
		ret = __subn_get_opa_led_info(smp, am, data, ibdev, port,
					      resp_len, max_len);
		break;
	case IB_SMP_ATTR_SM_INFO:
		if (ibp->rvp.port_cap_flags & IB_PORT_SM_DISABLED)
			return IB_MAD_RESULT_SUCCESS | IB_MAD_RESULT_CONSUMED;
		if (ibp->rvp.port_cap_flags & IB_PORT_SM)
			return IB_MAD_RESULT_SUCCESS;
		/* FALLTHROUGH */
	default:
		smp->status |= IB_SMP_UNSUP_METH_ATTR;
		ret = reply((struct ib_mad_hdr *)smp);
		break;
	}
	return ret;
}