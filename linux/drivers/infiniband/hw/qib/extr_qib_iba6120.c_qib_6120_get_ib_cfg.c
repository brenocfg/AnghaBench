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
struct qib_pportdata {int link_width_active; int link_speed_active; int link_width_enabled; int link_speed_enabled; int vls_operational; TYPE_2__* dd; } ;
struct TYPE_4__ {TYPE_1__* cspec; } ;
struct TYPE_3__ {int ibcctrl; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IBCCtrl ; 
 int IB_LINKINITCMD_POLL ; 
 int IB_LINKINITCMD_SLEEP ; 
 int /*<<< orphan*/  LinkDownDefaultState ; 
 int /*<<< orphan*/  OverrunThreshold ; 
 int /*<<< orphan*/  PhyerrThreshold ; 
#define  QIB_IB_CFG_HRTBT 139 
#define  QIB_IB_CFG_LINKDEFAULT 138 
#define  QIB_IB_CFG_LWID 137 
#define  QIB_IB_CFG_LWID_ENB 136 
#define  QIB_IB_CFG_OP_VLS 135 
#define  QIB_IB_CFG_OVERRUN_THRESH 134 
#define  QIB_IB_CFG_PHYERR_THRESH 133 
#define  QIB_IB_CFG_PMA_TICKS 132 
#define  QIB_IB_CFG_SPD 131 
#define  QIB_IB_CFG_SPD_ENB 130 
#define  QIB_IB_CFG_VL_HIGH_CAP 129 
#define  QIB_IB_CFG_VL_LOW_CAP 128 
 int SYM_FIELD (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int SYM_MASK (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qib_6120_get_ib_cfg(struct qib_pportdata *ppd, int which)
{
	int ret;

	switch (which) {
	case QIB_IB_CFG_LWID:
		ret = ppd->link_width_active;
		break;

	case QIB_IB_CFG_SPD:
		ret = ppd->link_speed_active;
		break;

	case QIB_IB_CFG_LWID_ENB:
		ret = ppd->link_width_enabled;
		break;

	case QIB_IB_CFG_SPD_ENB:
		ret = ppd->link_speed_enabled;
		break;

	case QIB_IB_CFG_OP_VLS:
		ret = ppd->vls_operational;
		break;

	case QIB_IB_CFG_VL_HIGH_CAP:
		ret = 0;
		break;

	case QIB_IB_CFG_VL_LOW_CAP:
		ret = 0;
		break;

	case QIB_IB_CFG_OVERRUN_THRESH: /* IB overrun threshold */
		ret = SYM_FIELD(ppd->dd->cspec->ibcctrl, IBCCtrl,
				OverrunThreshold);
		break;

	case QIB_IB_CFG_PHYERR_THRESH: /* IB PHY error threshold */
		ret = SYM_FIELD(ppd->dd->cspec->ibcctrl, IBCCtrl,
				PhyerrThreshold);
		break;

	case QIB_IB_CFG_LINKDEFAULT: /* IB link default (sleep/poll) */
		/* will only take effect when the link state changes */
		ret = (ppd->dd->cspec->ibcctrl &
		       SYM_MASK(IBCCtrl, LinkDownDefaultState)) ?
			IB_LINKINITCMD_SLEEP : IB_LINKINITCMD_POLL;
		break;

	case QIB_IB_CFG_HRTBT: /* Get Heartbeat off/enable/auto */
		ret = 0; /* no heartbeat on this chip */
		break;

	case QIB_IB_CFG_PMA_TICKS:
		ret = 250; /* 1 usec. */
		break;

	default:
		ret =  -EINVAL;
		break;
	}
	return ret;
}