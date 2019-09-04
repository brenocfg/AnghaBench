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
typedef  int u64 ;
struct qib_pportdata {int ibmaxlen; int link_speed_enabled; int link_width_enabled; int /*<<< orphan*/  guid; TYPE_1__* cpspec; struct qib_devdata* dd; } ;
struct qib_devdata {int control; int /*<<< orphan*/  base_guid; } ;
struct TYPE_2__ {int ibdeltainprog; int ibcctrl; int ibcddrctrl; void* iblnkerrsnap; void* ibsymsnap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CreditScale ; 
 int /*<<< orphan*/  FlowCtrlPeriod ; 
 int /*<<< orphan*/  FlowCtrlWaterMark ; 
 int IBA7220_IBC_HRTBT_MASK ; 
 int IBA7220_IBC_HRTBT_SHIFT ; 
 int IBA7220_IBC_IBTA_1_2_MASK ; 
 int IBA7220_IBC_LANE_REV_SUPPORTED ; 
 int IBA7220_IBC_RXPOL_MASK ; 
 int IBA7220_IBC_RXPOL_SHIFT ; 
 int IBA7220_IBC_SPEED_AUTONEG_MASK ; 
 int IBA7220_IBC_SPEED_DDR ; 
 int IBA7220_IBC_SPEED_SDR ; 
 int IBA7220_IBC_WIDTH_1X_ONLY ; 
 int IBA7220_IBC_WIDTH_4X_ONLY ; 
 int IBA7220_IBC_WIDTH_AUTONEG ; 
 int /*<<< orphan*/  IBCCtrl ; 
 int IB_WIDTH_1X ; 
 int IB_WIDTH_4X ; 
 int /*<<< orphan*/  MaxPktLen ; 
 int /*<<< orphan*/  OverrunThreshold ; 
 int /*<<< orphan*/  PhyerrThreshold ; 
 int QIB_IB_DDR ; 
 int QIB_IB_SDR ; 
 int QLOGIC_IB_C_LINKENABLE ; 
 int QLOGIC_IB_IBCC_LINKINITCMD_DISABLE ; 
 int QLOGIC_IB_IBCC_LINKINITCMD_SHIFT ; 
 int QLOGIC_IB_XGXS_FC_SAFE ; 
 int QLOGIC_IB_XGXS_RESET ; 
 int SYM_LSB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int be64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cr_iblinkerrrecov ; 
 int /*<<< orphan*/  cr_ibsymbolerr ; 
 int /*<<< orphan*/  kr_control ; 
 int /*<<< orphan*/  kr_hrtbt_guid ; 
 int /*<<< orphan*/  kr_ibcctrl ; 
 int /*<<< orphan*/  kr_ibcddrctrl ; 
 int /*<<< orphan*/  kr_ncmodectrl ; 
 int /*<<< orphan*/  kr_scratch ; 
 int /*<<< orphan*/  kr_xgxs_cfg ; 
 scalar_t__ qib_compat_ddr_negotiate ; 
 int /*<<< orphan*/  qib_read_kreg32 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 void* qib_read_kreg64 (struct qib_devdata*,int /*<<< orphan*/ ) ; 
 int qib_sd7220_init (struct qib_devdata*) ; 
 int /*<<< orphan*/  qib_write_kreg (struct qib_devdata*,int /*<<< orphan*/ ,int) ; 
 void* read_7220_creg32 (struct qib_devdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qib_7220_bringup_serdes(struct qib_pportdata *ppd)
{
	struct qib_devdata *dd = ppd->dd;
	u64 val, prev_val, guid, ibc;
	int ret = 0;

	/* Put IBC in reset, sends disabled */
	dd->control &= ~QLOGIC_IB_C_LINKENABLE;
	qib_write_kreg(dd, kr_control, 0ULL);

	if (qib_compat_ddr_negotiate) {
		ppd->cpspec->ibdeltainprog = 1;
		ppd->cpspec->ibsymsnap = read_7220_creg32(dd, cr_ibsymbolerr);
		ppd->cpspec->iblnkerrsnap =
			read_7220_creg32(dd, cr_iblinkerrrecov);
	}

	/* flowcontrolwatermark is in units of KBytes */
	ibc = 0x5ULL << SYM_LSB(IBCCtrl, FlowCtrlWaterMark);
	/*
	 * How often flowctrl sent.  More or less in usecs; balance against
	 * watermark value, so that in theory senders always get a flow
	 * control update in time to not let the IB link go idle.
	 */
	ibc |= 0x3ULL << SYM_LSB(IBCCtrl, FlowCtrlPeriod);
	/* max error tolerance */
	ibc |= 0xfULL << SYM_LSB(IBCCtrl, PhyerrThreshold);
	/* use "real" buffer space for */
	ibc |= 4ULL << SYM_LSB(IBCCtrl, CreditScale);
	/* IB credit flow control. */
	ibc |= 0xfULL << SYM_LSB(IBCCtrl, OverrunThreshold);
	/*
	 * set initial max size pkt IBC will send, including ICRC; it's the
	 * PIO buffer size in dwords, less 1; also see qib_set_mtu()
	 */
	ibc |= ((u64)(ppd->ibmaxlen >> 2) + 1) << SYM_LSB(IBCCtrl, MaxPktLen);
	ppd->cpspec->ibcctrl = ibc; /* without linkcmd or linkinitcmd! */

	/* initially come up waiting for TS1, without sending anything. */
	val = ppd->cpspec->ibcctrl | (QLOGIC_IB_IBCC_LINKINITCMD_DISABLE <<
		QLOGIC_IB_IBCC_LINKINITCMD_SHIFT);
	qib_write_kreg(dd, kr_ibcctrl, val);

	if (!ppd->cpspec->ibcddrctrl) {
		/* not on re-init after reset */
		ppd->cpspec->ibcddrctrl = qib_read_kreg64(dd, kr_ibcddrctrl);

		if (ppd->link_speed_enabled == (QIB_IB_SDR | QIB_IB_DDR))
			ppd->cpspec->ibcddrctrl |=
				IBA7220_IBC_SPEED_AUTONEG_MASK |
				IBA7220_IBC_IBTA_1_2_MASK;
		else
			ppd->cpspec->ibcddrctrl |=
				ppd->link_speed_enabled == QIB_IB_DDR ?
				IBA7220_IBC_SPEED_DDR : IBA7220_IBC_SPEED_SDR;
		if ((ppd->link_width_enabled & (IB_WIDTH_1X | IB_WIDTH_4X)) ==
		    (IB_WIDTH_1X | IB_WIDTH_4X))
			ppd->cpspec->ibcddrctrl |= IBA7220_IBC_WIDTH_AUTONEG;
		else
			ppd->cpspec->ibcddrctrl |=
				ppd->link_width_enabled == IB_WIDTH_4X ?
				IBA7220_IBC_WIDTH_4X_ONLY :
				IBA7220_IBC_WIDTH_1X_ONLY;

		/* always enable these on driver reload, not sticky */
		ppd->cpspec->ibcddrctrl |=
			IBA7220_IBC_RXPOL_MASK << IBA7220_IBC_RXPOL_SHIFT;
		ppd->cpspec->ibcddrctrl |=
			IBA7220_IBC_HRTBT_MASK << IBA7220_IBC_HRTBT_SHIFT;

		/* enable automatic lane reversal detection for receive */
		ppd->cpspec->ibcddrctrl |= IBA7220_IBC_LANE_REV_SUPPORTED;
	} else
		/* write to chip to prevent back-to-back writes of ibc reg */
		qib_write_kreg(dd, kr_scratch, 0);

	qib_write_kreg(dd, kr_ibcddrctrl, ppd->cpspec->ibcddrctrl);
	qib_write_kreg(dd, kr_scratch, 0);

	qib_write_kreg(dd, kr_ncmodectrl, 0Ull);
	qib_write_kreg(dd, kr_scratch, 0);

	ret = qib_sd7220_init(dd);

	val = qib_read_kreg64(dd, kr_xgxs_cfg);
	prev_val = val;
	val |= QLOGIC_IB_XGXS_FC_SAFE;
	if (val != prev_val) {
		qib_write_kreg(dd, kr_xgxs_cfg, val);
		qib_read_kreg32(dd, kr_scratch);
	}
	if (val & QLOGIC_IB_XGXS_RESET)
		val &= ~QLOGIC_IB_XGXS_RESET;
	if (val != prev_val)
		qib_write_kreg(dd, kr_xgxs_cfg, val);

	/* first time through, set port guid */
	if (!ppd->guid)
		ppd->guid = dd->base_guid;
	guid = be64_to_cpu(ppd->guid);

	qib_write_kreg(dd, kr_hrtbt_guid, guid);
	if (!ret) {
		dd->control |= QLOGIC_IB_C_LINKENABLE;
		qib_write_kreg(dd, kr_control, dd->control);
	} else
		/* write to chip to prevent back-to-back writes of ibc reg */
		qib_write_kreg(dd, kr_scratch, 0);
	return ret;
}