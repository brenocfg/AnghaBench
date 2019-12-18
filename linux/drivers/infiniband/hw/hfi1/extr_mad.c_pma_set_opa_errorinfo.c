#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct opa_port_error_info_msg {int /*<<< orphan*/  error_info_select_mask; int /*<<< orphan*/ * port_select_mask; struct _port_ei* port; } ;
struct TYPE_5__ {int /*<<< orphan*/  status; int /*<<< orphan*/  attr_mod; } ;
struct opa_pma_mad {TYPE_1__ mad_hdr; scalar_t__ data; } ;
struct ib_mad_hdr {int dummy; } ;
struct ib_device {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  status; } ;
struct TYPE_7__ {int /*<<< orphan*/  status; } ;
struct TYPE_6__ {int /*<<< orphan*/  status_and_code; } ;
struct hfi1_devdata {int /*<<< orphan*/  err_info_fmconfig; int /*<<< orphan*/  err_info_uncorrectable; TYPE_4__ err_info_rcv_constraint; TYPE_3__ err_info_xmit_constraint; TYPE_2__ err_info_rcvport; } ;
struct _port_ei {int dummy; } ;
typedef  int /*<<< orphan*/  port_mask ;

/* Variables and functions */
 int ES_EXCESSIVE_BUFFER_OVERRUN_INFO ; 
 int ES_FM_CONFIG_ERROR_INFO ; 
 int ES_PORT_RCV_CONSTRAINT_ERROR_INFO ; 
 int ES_PORT_RCV_ERROR_INFO ; 
 int ES_PORT_XMIT_CONSTRAINT_ERROR_INFO ; 
 int ES_UNCORRECTABLE_ERROR_INFO ; 
 int /*<<< orphan*/  IB_SMP_INVALID_FIELD ; 
 int OPA_AM_NPORT (int) ; 
 int /*<<< orphan*/  OPA_EI_STATUS_SMASK ; 
 int /*<<< orphan*/  RCV_ERR_INFO ; 
 int /*<<< orphan*/  RCV_ERR_INFO_RCV_EXCESS_BUFFER_OVERRUN_SMASK ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  be64_to_cpu (int /*<<< orphan*/ ) ; 
 struct hfi1_devdata* dd_from_ibdev (struct ib_device*) ; 
 int find_first_bit (unsigned long*,int) ; 
 int hweight64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct _port_ei*,int /*<<< orphan*/ ,int) ; 
 int reply (struct ib_mad_hdr*) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pma_set_opa_errorinfo(struct opa_pma_mad *pmp,
				 struct ib_device *ibdev,
				 u8 port, u32 *resp_len)
{
	struct _port_ei *rsp;
	struct opa_port_error_info_msg *req;
	struct hfi1_devdata *dd = dd_from_ibdev(ibdev);
	u64 port_mask;
	u32 num_ports;
	u8 port_num;
	u8 num_pslm;
	u32 error_info_select;

	req = (struct opa_port_error_info_msg *)pmp->data;
	rsp = &req->port[0];

	num_ports = OPA_AM_NPORT(be32_to_cpu(pmp->mad_hdr.attr_mod));
	num_pslm = hweight64(be64_to_cpu(req->port_select_mask[3]));

	memset(rsp, 0, sizeof(*rsp));

	if (num_ports != 1 || num_ports != num_pslm) {
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)pmp);
	}

	/*
	 * The bit set in the mask needs to be consistent with the port
	 * the request came in on.
	 */
	port_mask = be64_to_cpu(req->port_select_mask[3]);
	port_num = find_first_bit((unsigned long *)&port_mask,
				  sizeof(port_mask) * 8);

	if (port_num != port) {
		pmp->mad_hdr.status |= IB_SMP_INVALID_FIELD;
		return reply((struct ib_mad_hdr *)pmp);
	}

	error_info_select = be32_to_cpu(req->error_info_select_mask);

	/* PortRcvErrorInfo */
	if (error_info_select & ES_PORT_RCV_ERROR_INFO)
		/* turn off status bit */
		dd->err_info_rcvport.status_and_code &= ~OPA_EI_STATUS_SMASK;

	/* ExcessiverBufferOverrunInfo */
	if (error_info_select & ES_EXCESSIVE_BUFFER_OVERRUN_INFO)
		/*
		 * status bit is essentially kept in the h/w - bit 5 of
		 * RCV_ERR_INFO
		 */
		write_csr(dd, RCV_ERR_INFO,
			  RCV_ERR_INFO_RCV_EXCESS_BUFFER_OVERRUN_SMASK);

	if (error_info_select & ES_PORT_XMIT_CONSTRAINT_ERROR_INFO)
		dd->err_info_xmit_constraint.status &= ~OPA_EI_STATUS_SMASK;

	if (error_info_select & ES_PORT_RCV_CONSTRAINT_ERROR_INFO)
		dd->err_info_rcv_constraint.status &= ~OPA_EI_STATUS_SMASK;

	/* UncorrectableErrorInfo */
	if (error_info_select & ES_UNCORRECTABLE_ERROR_INFO)
		/* turn off status bit */
		dd->err_info_uncorrectable &= ~OPA_EI_STATUS_SMASK;

	/* FMConfigErrorInfo */
	if (error_info_select & ES_FM_CONFIG_ERROR_INFO)
		/* turn off status bit */
		dd->err_info_fmconfig &= ~OPA_EI_STATUS_SMASK;

	if (resp_len)
		*resp_len += sizeof(*req);

	return reply((struct ib_mad_hdr *)pmp);
}