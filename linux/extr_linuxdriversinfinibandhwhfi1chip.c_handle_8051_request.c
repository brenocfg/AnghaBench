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
typedef  int u64 ;
typedef  int u16 ;
struct hfi1_pportdata {struct hfi1_devdata* dd; } ;
struct hfi1_devdata {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DCC_CFG_RESET ; 
 int /*<<< orphan*/  DC_DC8051_CFG_EXT_DEV_0 ; 
 int /*<<< orphan*/  DC_DC8051_CFG_EXT_DEV_1 ; 
 int DC_DC8051_CFG_EXT_DEV_1_REQ_DATA_MASK ; 
 int DC_DC8051_CFG_EXT_DEV_1_REQ_DATA_SHIFT ; 
 int DC_DC8051_CFG_EXT_DEV_1_REQ_NEW_SMASK ; 
 int DC_DC8051_CFG_EXT_DEV_1_REQ_TYPE_MASK ; 
 int DC_DC8051_CFG_EXT_DEV_1_REQ_TYPE_SHIFT ; 
#define  HREQ_CONFIG_DONE 136 
#define  HREQ_ENABLE 135 
#define  HREQ_INTERFACE_TEST 134 
#define  HREQ_LCB_RESET 133 
#define  HREQ_LOAD_CONFIG 132 
 int /*<<< orphan*/  HREQ_NOT_SUPPORTED ; 
#define  HREQ_READ_CONFIG 131 
#define  HREQ_SAVE_CONFIG 130 
#define  HREQ_SET_TX_EQ_ABS 129 
#define  HREQ_SET_TX_EQ_REL 128 
 int /*<<< orphan*/  HREQ_SUCCESS ; 
 int /*<<< orphan*/  LCB_RX_FPE_TX_FPE_INTO_RESET ; 
 int /*<<< orphan*/  LCB_RX_FPE_TX_FPE_OUT_OF_RESET ; 
 int /*<<< orphan*/  dd_dev_err (struct hfi1_devdata*,char*,int) ; 
 int /*<<< orphan*/  dd_dev_info (struct hfi1_devdata*,char*,int) ; 
 int /*<<< orphan*/  hreq_response (struct hfi1_devdata*,int /*<<< orphan*/ ,int) ; 
 int read_csr (struct hfi1_devdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_csr (struct hfi1_devdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_8051_request(struct hfi1_pportdata *ppd)
{
	struct hfi1_devdata *dd = ppd->dd;
	u64 reg;
	u16 data = 0;
	u8 type;

	reg = read_csr(dd, DC_DC8051_CFG_EXT_DEV_1);
	if ((reg & DC_DC8051_CFG_EXT_DEV_1_REQ_NEW_SMASK) == 0)
		return;	/* no request */

	/* zero out COMPLETED so the response is seen */
	write_csr(dd, DC_DC8051_CFG_EXT_DEV_0, 0);

	/* extract request details */
	type = (reg >> DC_DC8051_CFG_EXT_DEV_1_REQ_TYPE_SHIFT)
			& DC_DC8051_CFG_EXT_DEV_1_REQ_TYPE_MASK;
	data = (reg >> DC_DC8051_CFG_EXT_DEV_1_REQ_DATA_SHIFT)
			& DC_DC8051_CFG_EXT_DEV_1_REQ_DATA_MASK;

	switch (type) {
	case HREQ_LOAD_CONFIG:
	case HREQ_SAVE_CONFIG:
	case HREQ_READ_CONFIG:
	case HREQ_SET_TX_EQ_ABS:
	case HREQ_SET_TX_EQ_REL:
	case HREQ_ENABLE:
		dd_dev_info(dd, "8051 request: request 0x%x not supported\n",
			    type);
		hreq_response(dd, HREQ_NOT_SUPPORTED, 0);
		break;
	case HREQ_LCB_RESET:
		/* Put the LCB, RX FPE and TX FPE into reset */
		write_csr(dd, DCC_CFG_RESET, LCB_RX_FPE_TX_FPE_INTO_RESET);
		/* Make sure the write completed */
		(void)read_csr(dd, DCC_CFG_RESET);
		/* Hold the reset long enough to take effect */
		udelay(1);
		/* Take the LCB, RX FPE and TX FPE out of reset */
		write_csr(dd, DCC_CFG_RESET, LCB_RX_FPE_TX_FPE_OUT_OF_RESET);
		hreq_response(dd, HREQ_SUCCESS, 0);

		break;
	case HREQ_CONFIG_DONE:
		hreq_response(dd, HREQ_SUCCESS, 0);
		break;

	case HREQ_INTERFACE_TEST:
		hreq_response(dd, HREQ_SUCCESS, data);
		break;
	default:
		dd_dev_err(dd, "8051 request: unknown request 0x%x\n", type);
		hreq_response(dd, HREQ_NOT_SUPPORTED, 0);
		break;
	}
}