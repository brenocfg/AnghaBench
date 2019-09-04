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
struct qib_pportdata {int link_width_enabled; int link_width_active; int link_speed_enabled; int link_speed_active; int vls_operational; TYPE_1__* cpspec; } ;
struct TYPE_2__ {int ibcctrl_a; int ibcctrl_b; } ;

/* Variables and functions */
 int EINVAL ; 
 int IBA7322_IBC_HRTBT_LSB ; 
 int IBA7322_IBC_HRTBT_RMASK ; 
 int /*<<< orphan*/  IBCCtrlA_0 ; 
 int /*<<< orphan*/  IBCCtrlB_0 ; 
 int /*<<< orphan*/  IBCStatusB_0 ; 
 int /*<<< orphan*/  IB_LANE_REV_SUPPORTED ; 
 int IB_LINKINITCMD_POLL ; 
 int IB_LINKINITCMD_SLEEP ; 
 int /*<<< orphan*/  IB_POLARITY_REV_SUPP ; 
 int /*<<< orphan*/  LinkDownDefaultState ; 
 int /*<<< orphan*/  LinkRoundTripLatency ; 
 int /*<<< orphan*/  OverrunThreshold ; 
 int /*<<< orphan*/  PhyerrThreshold ; 
#define  QIB_IB_CFG_HRTBT 142 
#define  QIB_IB_CFG_LINKDEFAULT 141 
#define  QIB_IB_CFG_LINKLATENCY 140 
#define  QIB_IB_CFG_LREV_ENB 139 
#define  QIB_IB_CFG_LWID 138 
#define  QIB_IB_CFG_LWID_ENB 137 
#define  QIB_IB_CFG_OP_VLS 136 
#define  QIB_IB_CFG_OVERRUN_THRESH 135 
#define  QIB_IB_CFG_PHYERR_THRESH 134 
#define  QIB_IB_CFG_PMA_TICKS 133 
#define  QIB_IB_CFG_RXPOL_ENB 132 
#define  QIB_IB_CFG_SPD 131 
#define  QIB_IB_CFG_SPD_ENB 130 
#define  QIB_IB_CFG_VL_HIGH_CAP 129 
#define  QIB_IB_CFG_VL_LOW_CAP 128 
 int QIB_IB_DDR ; 
 int QIB_IB_QDR ; 
 int SYM_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SYM_LSB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SYM_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SYM_RMASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  krp_ibcstatus_b ; 
 int qib_read_kreg_port (struct qib_pportdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qib_7322_get_ib_cfg(struct qib_pportdata *ppd, int which)
{

	int lsb, ret = 0;
	u64 maskr; /* right-justified mask */

	switch (which) {

	case QIB_IB_CFG_LWID_ENB: /* Get allowed Link-width */
		ret = ppd->link_width_enabled;
		goto done;

	case QIB_IB_CFG_LWID: /* Get currently active Link-width */
		ret = ppd->link_width_active;
		goto done;

	case QIB_IB_CFG_SPD_ENB: /* Get allowed Link speeds */
		ret = ppd->link_speed_enabled;
		goto done;

	case QIB_IB_CFG_SPD: /* Get current Link spd */
		ret = ppd->link_speed_active;
		goto done;

	case QIB_IB_CFG_RXPOL_ENB: /* Get Auto-RX-polarity enable */
		lsb = SYM_LSB(IBCCtrlB_0, IB_POLARITY_REV_SUPP);
		maskr = SYM_RMASK(IBCCtrlB_0, IB_POLARITY_REV_SUPP);
		break;

	case QIB_IB_CFG_LREV_ENB: /* Get Auto-Lane-reversal enable */
		lsb = SYM_LSB(IBCCtrlB_0, IB_LANE_REV_SUPPORTED);
		maskr = SYM_RMASK(IBCCtrlB_0, IB_LANE_REV_SUPPORTED);
		break;

	case QIB_IB_CFG_LINKLATENCY:
		ret = qib_read_kreg_port(ppd, krp_ibcstatus_b) &
			SYM_MASK(IBCStatusB_0, LinkRoundTripLatency);
		goto done;

	case QIB_IB_CFG_OP_VLS:
		ret = ppd->vls_operational;
		goto done;

	case QIB_IB_CFG_VL_HIGH_CAP:
		ret = 16;
		goto done;

	case QIB_IB_CFG_VL_LOW_CAP:
		ret = 16;
		goto done;

	case QIB_IB_CFG_OVERRUN_THRESH: /* IB overrun threshold */
		ret = SYM_FIELD(ppd->cpspec->ibcctrl_a, IBCCtrlA_0,
				OverrunThreshold);
		goto done;

	case QIB_IB_CFG_PHYERR_THRESH: /* IB PHY error threshold */
		ret = SYM_FIELD(ppd->cpspec->ibcctrl_a, IBCCtrlA_0,
				PhyerrThreshold);
		goto done;

	case QIB_IB_CFG_LINKDEFAULT: /* IB link default (sleep/poll) */
		/* will only take effect when the link state changes */
		ret = (ppd->cpspec->ibcctrl_a &
		       SYM_MASK(IBCCtrlA_0, LinkDownDefaultState)) ?
			IB_LINKINITCMD_SLEEP : IB_LINKINITCMD_POLL;
		goto done;

	case QIB_IB_CFG_HRTBT: /* Get Heartbeat off/enable/auto */
		lsb = IBA7322_IBC_HRTBT_LSB;
		maskr = IBA7322_IBC_HRTBT_RMASK; /* OR of AUTO and ENB */
		break;

	case QIB_IB_CFG_PMA_TICKS:
		/*
		 * 0x00 = 10x link transfer rate or 4 nsec. for 2.5Gbs
		 * Since the clock is always 250MHz, the value is 3, 1 or 0.
		 */
		if (ppd->link_speed_active == QIB_IB_QDR)
			ret = 3;
		else if (ppd->link_speed_active == QIB_IB_DDR)
			ret = 1;
		else
			ret = 0;
		goto done;

	default:
		ret = -EINVAL;
		goto done;
	}
	ret = (int)((ppd->cpspec->ibcctrl_b >> lsb) & maskr);
done:
	return ret;
}