#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_10__ {int online; } ;
struct TYPE_13__ {int qlini_mode; scalar_t__ u_ql2xexchoffld; scalar_t__ ql2xexchoffld; scalar_t__ u_ql2xiniexchg; scalar_t__ ql2xiniexchg; int /*<<< orphan*/  dpc_flags; TYPE_1__ flags; TYPE_3__* hw; } ;
typedef  TYPE_4__ scsi_qla_host_t ;
struct TYPE_11__ {int /*<<< orphan*/  exchoffld_enabled; int /*<<< orphan*/  fw_started; } ;
struct TYPE_12__ {TYPE_2__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ISP_ABORT_NEEDED ; 
 int /*<<< orphan*/  NEED_EXCH_OFFLOAD (scalar_t__) ; 
#define  QLA2XXX_INI_MODE_DISABLED 131 
#define  QLA2XXX_INI_MODE_DUAL 130 
#define  QLA2XXX_INI_MODE_ENABLED 129 
#define  QLA2XXX_INI_MODE_EXCLUSIVE 128 
 int /*<<< orphan*/ * mode_to_str ; 
 int /*<<< orphan*/  ql_log (int /*<<< orphan*/ ,TYPE_4__*,int,char*,...) ; 
 int /*<<< orphan*/  ql_log_warn ; 
 int /*<<< orphan*/  qla_dual_mode_enabled (TYPE_4__*) ; 
 int /*<<< orphan*/  qla_tgt_mode_enabled (TYPE_4__*) ; 
 int /*<<< orphan*/  qlt_set_mode (TYPE_4__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qla_set_ini_mode(scsi_qla_host_t *vha, int op)
{
	int rc = 0;
	enum {
		NO_ACTION,
		MODE_CHANGE_ACCEPT,
		MODE_CHANGE_NO_ACTION,
		TARGET_STILL_ACTIVE,
	};
	int action = NO_ACTION;
	int set_mode = 0;
	u8  eo_toggle = 0;	/* exchange offload flipped */

	switch (vha->qlini_mode) {
	case QLA2XXX_INI_MODE_DISABLED:
		switch (op) {
		case QLA2XXX_INI_MODE_DISABLED:
			if (qla_tgt_mode_enabled(vha)) {
				if (NEED_EXCH_OFFLOAD(vha->u_ql2xexchoffld) !=
				    vha->hw->flags.exchoffld_enabled)
					eo_toggle = 1;
				if (((vha->ql2xexchoffld !=
				    vha->u_ql2xexchoffld) &&
				    NEED_EXCH_OFFLOAD(vha->u_ql2xexchoffld)) ||
				    eo_toggle) {
					/*
					 * The number of exchange to be offload
					 * was tweaked or offload option was
					 * flipped
					 */
					action = MODE_CHANGE_ACCEPT;
				} else {
					action = MODE_CHANGE_NO_ACTION;
				}
			} else {
				action = MODE_CHANGE_NO_ACTION;
			}
			break;
		case QLA2XXX_INI_MODE_EXCLUSIVE:
			if (qla_tgt_mode_enabled(vha)) {
				if (NEED_EXCH_OFFLOAD(vha->u_ql2xexchoffld) !=
				    vha->hw->flags.exchoffld_enabled)
					eo_toggle = 1;
				if (((vha->ql2xexchoffld !=
				    vha->u_ql2xexchoffld) &&
				    NEED_EXCH_OFFLOAD(vha->u_ql2xexchoffld)) ||
				    eo_toggle) {
					/*
					 * The number of exchange to be offload
					 * was tweaked or offload option was
					 * flipped
					 */
					action = MODE_CHANGE_ACCEPT;
				} else {
					action = MODE_CHANGE_NO_ACTION;
				}
			} else {
				action = MODE_CHANGE_ACCEPT;
			}
			break;
		case QLA2XXX_INI_MODE_DUAL:
			action = MODE_CHANGE_ACCEPT;
			/* active_mode is target only, reset it to dual */
			if (qla_tgt_mode_enabled(vha)) {
				set_mode = 1;
				action = MODE_CHANGE_ACCEPT;
			} else {
				action = MODE_CHANGE_NO_ACTION;
			}
			break;

		case QLA2XXX_INI_MODE_ENABLED:
			if (qla_tgt_mode_enabled(vha))
				action = TARGET_STILL_ACTIVE;
			else {
				action = MODE_CHANGE_ACCEPT;
				set_mode = 1;
			}
			break;
		}
		break;

	case QLA2XXX_INI_MODE_EXCLUSIVE:
		switch (op) {
		case QLA2XXX_INI_MODE_EXCLUSIVE:
			if (qla_tgt_mode_enabled(vha)) {
				if (NEED_EXCH_OFFLOAD(vha->u_ql2xexchoffld) !=
				    vha->hw->flags.exchoffld_enabled)
					eo_toggle = 1;
				if (((vha->ql2xexchoffld !=
				    vha->u_ql2xexchoffld) &&
				    NEED_EXCH_OFFLOAD(vha->u_ql2xexchoffld)) ||
				    eo_toggle)
					/*
					 * The number of exchange to be offload
					 * was tweaked or offload option was
					 * flipped
					 */
					action = MODE_CHANGE_ACCEPT;
				else
					action = NO_ACTION;
			} else
				action = NO_ACTION;

			break;

		case QLA2XXX_INI_MODE_DISABLED:
			if (qla_tgt_mode_enabled(vha)) {
				if (NEED_EXCH_OFFLOAD(vha->u_ql2xexchoffld) !=
				    vha->hw->flags.exchoffld_enabled)
					eo_toggle = 1;
				if (((vha->ql2xexchoffld !=
				      vha->u_ql2xexchoffld) &&
				    NEED_EXCH_OFFLOAD(vha->u_ql2xexchoffld)) ||
				    eo_toggle)
					action = MODE_CHANGE_ACCEPT;
				else
					action = MODE_CHANGE_NO_ACTION;
			} else
				action = MODE_CHANGE_NO_ACTION;
			break;

		case QLA2XXX_INI_MODE_DUAL: /* exclusive -> dual */
			if (qla_tgt_mode_enabled(vha)) {
				action = MODE_CHANGE_ACCEPT;
				set_mode = 1;
			} else
				action = MODE_CHANGE_ACCEPT;
			break;

		case QLA2XXX_INI_MODE_ENABLED:
			if (qla_tgt_mode_enabled(vha))
				action = TARGET_STILL_ACTIVE;
			else {
				if (vha->hw->flags.fw_started)
					action = MODE_CHANGE_NO_ACTION;
				else
					action = MODE_CHANGE_ACCEPT;
			}
			break;
		}
		break;

	case QLA2XXX_INI_MODE_ENABLED:
		switch (op) {
		case QLA2XXX_INI_MODE_ENABLED:
			if (NEED_EXCH_OFFLOAD(vha->u_ql2xiniexchg) !=
			    vha->hw->flags.exchoffld_enabled)
				eo_toggle = 1;
			if (((vha->ql2xiniexchg != vha->u_ql2xiniexchg) &&
				NEED_EXCH_OFFLOAD(vha->u_ql2xiniexchg)) ||
			    eo_toggle)
				action = MODE_CHANGE_ACCEPT;
			else
				action = NO_ACTION;
			break;
		case QLA2XXX_INI_MODE_DUAL:
		case QLA2XXX_INI_MODE_DISABLED:
			action = MODE_CHANGE_ACCEPT;
			break;
		default:
			action = MODE_CHANGE_NO_ACTION;
			break;
		}
		break;

	case QLA2XXX_INI_MODE_DUAL:
		switch (op) {
		case QLA2XXX_INI_MODE_DUAL:
			if (qla_tgt_mode_enabled(vha) ||
			    qla_dual_mode_enabled(vha)) {
				if (NEED_EXCH_OFFLOAD(vha->u_ql2xexchoffld +
					vha->u_ql2xiniexchg) !=
				    vha->hw->flags.exchoffld_enabled)
					eo_toggle = 1;

				if ((((vha->ql2xexchoffld +
				       vha->ql2xiniexchg) !=
				    (vha->u_ql2xiniexchg +
				     vha->u_ql2xexchoffld)) &&
				    NEED_EXCH_OFFLOAD(vha->u_ql2xiniexchg +
					vha->u_ql2xexchoffld)) || eo_toggle)
					action = MODE_CHANGE_ACCEPT;
				else
					action = NO_ACTION;
			} else {
				if (NEED_EXCH_OFFLOAD(vha->u_ql2xexchoffld +
					vha->u_ql2xiniexchg) !=
				    vha->hw->flags.exchoffld_enabled)
					eo_toggle = 1;

				if ((((vha->ql2xexchoffld + vha->ql2xiniexchg)
				    != (vha->u_ql2xiniexchg +
					vha->u_ql2xexchoffld)) &&
				    NEED_EXCH_OFFLOAD(vha->u_ql2xiniexchg +
					vha->u_ql2xexchoffld)) || eo_toggle)
					action = MODE_CHANGE_NO_ACTION;
				else
					action = NO_ACTION;
			}
			break;

		case QLA2XXX_INI_MODE_DISABLED:
			if (qla_tgt_mode_enabled(vha) ||
			    qla_dual_mode_enabled(vha)) {
				/* turning off initiator mode */
				set_mode = 1;
				action = MODE_CHANGE_ACCEPT;
			} else {
				action = MODE_CHANGE_NO_ACTION;
			}
			break;

		case QLA2XXX_INI_MODE_EXCLUSIVE:
			if (qla_tgt_mode_enabled(vha) ||
			    qla_dual_mode_enabled(vha)) {
				set_mode = 1;
				action = MODE_CHANGE_ACCEPT;
			} else {
				action = MODE_CHANGE_ACCEPT;
			}
			break;

		case QLA2XXX_INI_MODE_ENABLED:
			if (qla_tgt_mode_enabled(vha) ||
			    qla_dual_mode_enabled(vha)) {
				action = TARGET_STILL_ACTIVE;
			} else {
				action = MODE_CHANGE_ACCEPT;
			}
		}
		break;
	}

	switch (action) {
	case MODE_CHANGE_ACCEPT:
		ql_log(ql_log_warn, vha, 0xffff,
		    "Mode change accepted. From %s to %s, Tgt exchg %d|%d. ini exchg %d|%d\n",
		    mode_to_str[vha->qlini_mode], mode_to_str[op],
		    vha->ql2xexchoffld, vha->u_ql2xexchoffld,
		    vha->ql2xiniexchg, vha->u_ql2xiniexchg);

		vha->qlini_mode = op;
		vha->ql2xexchoffld = vha->u_ql2xexchoffld;
		vha->ql2xiniexchg = vha->u_ql2xiniexchg;
		if (set_mode)
			qlt_set_mode(vha);
		vha->flags.online = 1;
		set_bit(ISP_ABORT_NEEDED, &vha->dpc_flags);
		break;

	case MODE_CHANGE_NO_ACTION:
		ql_log(ql_log_warn, vha, 0xffff,
		    "Mode is set. No action taken. From %s to %s, Tgt exchg %d|%d. ini exchg %d|%d\n",
		    mode_to_str[vha->qlini_mode], mode_to_str[op],
		    vha->ql2xexchoffld, vha->u_ql2xexchoffld,
		    vha->ql2xiniexchg, vha->u_ql2xiniexchg);
		vha->qlini_mode = op;
		vha->ql2xexchoffld = vha->u_ql2xexchoffld;
		vha->ql2xiniexchg = vha->u_ql2xiniexchg;
		break;

	case TARGET_STILL_ACTIVE:
		ql_log(ql_log_warn, vha, 0xffff,
		    "Target Mode is active. Unable to change Mode.\n");
		break;

	case NO_ACTION:
	default:
		ql_log(ql_log_warn, vha, 0xffff,
		    "Mode unchange. No action taken. %d|%d pct %d|%d.\n",
		    vha->qlini_mode, op,
		    vha->ql2xexchoffld, vha->u_ql2xexchoffld);
		break;
	}

	return rc;
}