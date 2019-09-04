#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_3__ {int /*<<< orphan*/  return_path; int /*<<< orphan*/  dr_slid; } ;
struct TYPE_4__ {TYPE_1__ dr; } ;
struct opa_smp {scalar_t__ attr_id; scalar_t__ class_version; int method; int /*<<< orphan*/  status; int /*<<< orphan*/  hop_cnt; TYPE_2__ route; int /*<<< orphan*/  mkey; int /*<<< orphan*/  attr_mod; } ;
struct opa_mad {int dummy; } ;
struct ib_mad_hdr {int dummy; } ;
struct ib_device {scalar_t__ phys_port_cnt; } ;
struct hfi1_ibport {int dummy; } ;
typedef  scalar_t__ __be16 ;

/* Variables and functions */
 int IB_MAD_RESULT_FAILURE ; 
 int IB_MAD_RESULT_SUCCESS ; 
#define  IB_MGMT_METHOD_GET 135 
#define  IB_MGMT_METHOD_GET_RESP 134 
#define  IB_MGMT_METHOD_REPORT 133 
#define  IB_MGMT_METHOD_REPORT_RESP 132 
#define  IB_MGMT_METHOD_SET 131 
#define  IB_MGMT_METHOD_TRAP 130 
#define  IB_MGMT_METHOD_TRAP_REPRESS 129 
 scalar_t__ IB_SMP_ATTR_PORT_INFO ; 
 int /*<<< orphan*/  IB_SMP_UNSUP_METHOD ; 
 int /*<<< orphan*/  IB_SMP_UNSUP_VERSION ; 
#define  OPA_ATTRIB_ID_AGGREGATE 128 
 scalar_t__ OPA_SM_CLASS_VERSION ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int check_mkey (struct hfi1_ibport*,struct ib_mad_hdr*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_opa_smp_data (struct opa_smp*) ; 
 scalar_t__* opa_get_smp_data (struct opa_smp*) ; 
 scalar_t__ opa_get_smp_data_size (struct opa_smp*) ; 
 scalar_t__ opa_get_smp_header_size (struct opa_smp*) ; 
 int reply (struct ib_mad_hdr*) ; 
 int subn_get_opa_aggregate (struct opa_smp*,struct ib_device*,scalar_t__,scalar_t__*) ; 
 int subn_get_opa_sma (scalar_t__,struct opa_smp*,scalar_t__,scalar_t__*,struct ib_device*,scalar_t__,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  subn_handle_opa_trap_repress (struct hfi1_ibport*,struct opa_smp*) ; 
 int subn_set_opa_aggregate (struct opa_smp*,struct ib_device*,scalar_t__,scalar_t__*,int) ; 
 int subn_set_opa_sma (scalar_t__,struct opa_smp*,scalar_t__,scalar_t__*,struct ib_device*,scalar_t__,scalar_t__*,scalar_t__,int) ; 
 struct hfi1_ibport* to_iport (struct ib_device*,scalar_t__) ; 

__attribute__((used)) static int process_subn_opa(struct ib_device *ibdev, int mad_flags,
			    u8 port, const struct opa_mad *in_mad,
			    struct opa_mad *out_mad,
			    u32 *resp_len, int local_mad)
{
	struct opa_smp *smp = (struct opa_smp *)out_mad;
	struct hfi1_ibport *ibp = to_iport(ibdev, port);
	u8 *data;
	u32 am, data_size;
	__be16 attr_id;
	int ret;

	*out_mad = *in_mad;
	data = opa_get_smp_data(smp);
	data_size = (u32)opa_get_smp_data_size(smp);

	am = be32_to_cpu(smp->attr_mod);
	attr_id = smp->attr_id;
	if (smp->class_version != OPA_SM_CLASS_VERSION) {
		smp->status |= IB_SMP_UNSUP_VERSION;
		ret = reply((struct ib_mad_hdr *)smp);
		return ret;
	}
	ret = check_mkey(ibp, (struct ib_mad_hdr *)smp, mad_flags, smp->mkey,
			 smp->route.dr.dr_slid, smp->route.dr.return_path,
			 smp->hop_cnt);
	if (ret) {
		u32 port_num = be32_to_cpu(smp->attr_mod);

		/*
		 * If this is a get/set portinfo, we already check the
		 * M_Key if the MAD is for another port and the M_Key
		 * is OK on the receiving port. This check is needed
		 * to increment the error counters when the M_Key
		 * fails to match on *both* ports.
		 */
		if (attr_id == IB_SMP_ATTR_PORT_INFO &&
		    (smp->method == IB_MGMT_METHOD_GET ||
		     smp->method == IB_MGMT_METHOD_SET) &&
		    port_num && port_num <= ibdev->phys_port_cnt &&
		    port != port_num)
			(void)check_mkey(to_iport(ibdev, port_num),
					  (struct ib_mad_hdr *)smp, 0,
					  smp->mkey, smp->route.dr.dr_slid,
					  smp->route.dr.return_path,
					  smp->hop_cnt);
		ret = IB_MAD_RESULT_FAILURE;
		return ret;
	}

	*resp_len = opa_get_smp_header_size(smp);

	switch (smp->method) {
	case IB_MGMT_METHOD_GET:
		switch (attr_id) {
		default:
			clear_opa_smp_data(smp);
			ret = subn_get_opa_sma(attr_id, smp, am, data,
					       ibdev, port, resp_len,
					       data_size);
			break;
		case OPA_ATTRIB_ID_AGGREGATE:
			ret = subn_get_opa_aggregate(smp, ibdev, port,
						     resp_len);
			break;
		}
		break;
	case IB_MGMT_METHOD_SET:
		switch (attr_id) {
		default:
			ret = subn_set_opa_sma(attr_id, smp, am, data,
					       ibdev, port, resp_len,
					       data_size, local_mad);
			break;
		case OPA_ATTRIB_ID_AGGREGATE:
			ret = subn_set_opa_aggregate(smp, ibdev, port,
						     resp_len, local_mad);
			break;
		}
		break;
	case IB_MGMT_METHOD_TRAP:
	case IB_MGMT_METHOD_REPORT:
	case IB_MGMT_METHOD_REPORT_RESP:
	case IB_MGMT_METHOD_GET_RESP:
		/*
		 * The ib_mad module will call us to process responses
		 * before checking for other consumers.
		 * Just tell the caller to process it normally.
		 */
		ret = IB_MAD_RESULT_SUCCESS;
		break;
	case IB_MGMT_METHOD_TRAP_REPRESS:
		subn_handle_opa_trap_repress(ibp, smp);
		/* Always successful */
		ret = IB_MAD_RESULT_SUCCESS;
		break;
	default:
		smp->status |= IB_SMP_UNSUP_METHOD;
		ret = reply((struct ib_mad_hdr *)smp);
		break;
	}

	return ret;
}