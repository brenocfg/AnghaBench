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
struct qib_pportdata {int link_width_enabled; int link_width_active; int link_speed_enabled; int link_speed_active; int vls_operational; TYPE_1__* cpspec; int /*<<< orphan*/  dd; } ;
struct TYPE_2__ {int ibcctrl; int ibcddrctrl; } ;

/* Variables and functions */
 int EINVAL ; 
 int IBA7220_DDRSTAT_LINKLAT_MASK ; 
 int IBA7220_IBC_HRTBT_MASK ; 
 int IBA7220_IBC_HRTBT_SHIFT ; 
 int IBA7220_IBC_LREV_MASK ; 
 int IBA7220_IBC_LREV_SHIFT ; 
 int IBA7220_IBC_RXPOL_MASK ; 
 int IBA7220_IBC_RXPOL_SHIFT ; 
 int /*<<< orphan*/  IBCCtrl ; 
 int IB_LINKINITCMD_POLL ; 
 int IB_LINKINITCMD_SLEEP ; 
 int /*<<< orphan*/  LinkDownDefaultState ; 
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
 int SYM_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SYM_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kr_ibcddrstatus ; 
 int qib_read_kreg64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qib_7220_get_ib_cfg(struct qib_pportdata *ppd, int which)
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
		lsb = IBA7220_IBC_RXPOL_SHIFT;
		maskr = IBA7220_IBC_RXPOL_MASK;
		break;

	case QIB_IB_CFG_LREV_ENB: /* Get Auto-Lane-reversal enable */
		lsb = IBA7220_IBC_LREV_SHIFT;
		maskr = IBA7220_IBC_LREV_MASK;
		break;

	case QIB_IB_CFG_LINKLATENCY:
		ret = qib_read_kreg64(ppd->dd, kr_ibcddrstatus)
			& IBA7220_DDRSTAT_LINKLAT_MASK;
		goto done;

	case QIB_IB_CFG_OP_VLS:
		ret = ppd->vls_operational;
		goto done;

	case QIB_IB_CFG_VL_HIGH_CAP:
		ret = 0;
		goto done;

	case QIB_IB_CFG_VL_LOW_CAP:
		ret = 0;
		goto done;

	case QIB_IB_CFG_OVERRUN_THRESH: /* IB overrun threshold */
		ret = SYM_FIELD(ppd->cpspec->ibcctrl, IBCCtrl,
				OverrunThreshold);
		goto done;

	case QIB_IB_CFG_PHYERR_THRESH: /* IB PHY error threshold */
		ret = SYM_FIELD(ppd->cpspec->ibcctrl, IBCCtrl,
				PhyerrThreshold);
		goto done;

	case QIB_IB_CFG_LINKDEFAULT: /* IB link default (sleep/poll) */
		/* will only take effect when the link state changes */
		ret = (ppd->cpspec->ibcctrl &
		       SYM_MASK(IBCCtrl, LinkDownDefaultState)) ?
			IB_LINKINITCMD_SLEEP : IB_LINKINITCMD_POLL;
		goto done;

	case QIB_IB_CFG_HRTBT: /* Get Heartbeat off/enable/auto */
		lsb = IBA7220_IBC_HRTBT_SHIFT;
		maskr = IBA7220_IBC_HRTBT_MASK;
		break;

	case QIB_IB_CFG_PMA_TICKS:
		/*
		 * 0x00 = 10x link transfer rate or 4 nsec. for 2.5Gbs
		 * Since the clock is always 250MHz, the value is 1 or 0.
		 */
		ret = (ppd->link_speed_active == QIB_IB_DDR);
		goto done;

	default:
		ret = -EINVAL;
		goto done;
	}
	ret = (int)((ppd->cpspec->ibcddrctrl >> lsb) & maskr);
done:
	return ret;
}