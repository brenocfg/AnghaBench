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
typedef  scalar_t__ u64 ;
typedef  scalar_t__ u32 ;
struct ib_device {int dummy; } ;
struct hfi1_pportdata {int dummy; } ;
struct hfi1_ibport {int dummy; } ;
struct hfi1_devdata {int dummy; } ;
struct _port_ectrs {void* excessive_buffer_overruns; void* local_link_integrity_errors; void* port_rcv_constraint_errors; void* port_xmit_constraint_errors; void* port_xmit_discards; scalar_t__ port_rcv_switch_relay_errors; void* port_rcv_remote_physical_errors; void* port_rcv_errors; void* link_downed; void* link_error_recovery; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNTR_INVALID_VL ; 
 int /*<<< orphan*/  C_DC_RCV_ERR ; 
 int /*<<< orphan*/  C_DC_REINIT_FROM_PEER_CNT ; 
 int /*<<< orphan*/  C_DC_RMT_PHY_ERR ; 
 int /*<<< orphan*/  C_DC_RX_REPLAY ; 
 int /*<<< orphan*/  C_DC_SEQ_CRC_CNT ; 
 int /*<<< orphan*/  C_RCV_OVF ; 
 int /*<<< orphan*/  C_SW_LINK_DOWN ; 
 int /*<<< orphan*/  C_SW_RCV_CSTR_ERR ; 
 int /*<<< orphan*/  C_SW_XMIT_CSTR_ERR ; 
 int /*<<< orphan*/  C_SW_XMIT_DSCD ; 
 scalar_t__ UINT_MAX ; 
 void* cpu_to_be32 (scalar_t__) ; 
 void* cpu_to_be64 (scalar_t__) ; 
 struct hfi1_devdata* dd_from_ibdev (struct ib_device*) ; 
 struct hfi1_pportdata* ppd_from_ibp (struct hfi1_ibport*) ; 
 scalar_t__ read_dev_cntr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ read_port_cntr (struct hfi1_pportdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct hfi1_ibport* to_iport (struct ib_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void pma_get_opa_port_ectrs(struct ib_device *ibdev,
				   struct _port_ectrs *rsp, u8 port)
{
	u64 tmp, tmp2;
	struct hfi1_devdata *dd = dd_from_ibdev(ibdev);
	struct hfi1_ibport *ibp = to_iport(ibdev, port);
	struct hfi1_pportdata *ppd = ppd_from_ibp(ibp);

	tmp = read_dev_cntr(dd, C_DC_SEQ_CRC_CNT, CNTR_INVALID_VL);
	tmp2 = tmp + read_dev_cntr(dd, C_DC_REINIT_FROM_PEER_CNT,
					CNTR_INVALID_VL);
	if (tmp2 > (u32)UINT_MAX || tmp2 < tmp) {
		/* overflow/wrapped */
		rsp->link_error_recovery = cpu_to_be32(~0);
	} else {
		rsp->link_error_recovery = cpu_to_be32(tmp2);
	}

	rsp->link_downed = cpu_to_be32(read_port_cntr(ppd, C_SW_LINK_DOWN,
						CNTR_INVALID_VL));
	rsp->port_rcv_errors =
		cpu_to_be64(read_dev_cntr(dd, C_DC_RCV_ERR, CNTR_INVALID_VL));
	rsp->port_rcv_remote_physical_errors =
		cpu_to_be64(read_dev_cntr(dd, C_DC_RMT_PHY_ERR,
					  CNTR_INVALID_VL));
	rsp->port_rcv_switch_relay_errors = 0;
	rsp->port_xmit_discards =
		cpu_to_be64(read_port_cntr(ppd, C_SW_XMIT_DSCD,
					   CNTR_INVALID_VL));
	rsp->port_xmit_constraint_errors =
		cpu_to_be64(read_port_cntr(ppd, C_SW_XMIT_CSTR_ERR,
					   CNTR_INVALID_VL));
	rsp->port_rcv_constraint_errors =
		cpu_to_be64(read_port_cntr(ppd, C_SW_RCV_CSTR_ERR,
					   CNTR_INVALID_VL));
	rsp->local_link_integrity_errors =
		cpu_to_be64(read_dev_cntr(dd, C_DC_RX_REPLAY,
					  CNTR_INVALID_VL));
	rsp->excessive_buffer_overruns =
		cpu_to_be64(read_dev_cntr(dd, C_RCV_OVF, CNTR_INVALID_VL));
}