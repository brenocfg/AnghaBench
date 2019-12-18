#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
typedef  int u8 ;
struct scsi_qla_host {int dummy; } ;
struct port_database_24xx {int current_login_state; int last_login_state; int* prli_svc_param_word_3; int flags; int /*<<< orphan*/ * port_id; int /*<<< orphan*/ * port_name; int /*<<< orphan*/ * node_name; } ;
struct TYPE_5__ {scalar_t__ rsvd_1; int /*<<< orphan*/  al_pa; int /*<<< orphan*/  area; int /*<<< orphan*/  domain; } ;
struct TYPE_6__ {TYPE_1__ b; } ;
struct TYPE_7__ {int conf_compl_supported; int /*<<< orphan*/  flags; int /*<<< orphan*/  supported_classes; int /*<<< orphan*/  port_type; scalar_t__ fc4f_nvme; TYPE_2__ d_id; int /*<<< orphan*/  port_name; int /*<<< orphan*/  node_name; int /*<<< orphan*/  loop_id; } ;
typedef  TYPE_3__ fc_port_t ;

/* Variables and functions */
 int BIT_3 ; 
 int BIT_4 ; 
 int BIT_5 ; 
 int BIT_7 ; 
 int /*<<< orphan*/  FCF_CONF_COMP_SUPPORTED ; 
 int /*<<< orphan*/  FCT_INITIATOR ; 
 int /*<<< orphan*/  FCT_NVME_DISCOVERY ; 
 int /*<<< orphan*/  FCT_NVME_INITIATOR ; 
 int /*<<< orphan*/  FCT_NVME_TARGET ; 
 int /*<<< orphan*/  FCT_TARGET ; 
 int /*<<< orphan*/  FC_COS_CLASS2 ; 
 int /*<<< orphan*/  FC_COS_CLASS3 ; 
 int /*<<< orphan*/  FC_NO_LOOP_ID ; 
 int PDF_CLASS_2 ; 
 int PDS_PRLI_COMPLETE ; 
 int QLA_FUNCTION_FAILED ; 
 int QLA_NOT_LOGGED_IN ; 
 int QLA_SUCCESS ; 
 int /*<<< orphan*/  WWN_SIZE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg (int /*<<< orphan*/ ,struct scsi_qla_host*,int,char*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_dbg_mbx ; 

int __qla24xx_parse_gpdb(struct scsi_qla_host *vha, fc_port_t *fcport,
    struct port_database_24xx *pd)
{
	int rval = QLA_SUCCESS;
	uint64_t zero = 0;
	u8 current_login_state, last_login_state;

	if (fcport->fc4f_nvme) {
		current_login_state = pd->current_login_state >> 4;
		last_login_state = pd->last_login_state >> 4;
	} else {
		current_login_state = pd->current_login_state & 0xf;
		last_login_state = pd->last_login_state & 0xf;
	}

	/* Check for logged in state. */
	if (current_login_state != PDS_PRLI_COMPLETE) {
		ql_dbg(ql_dbg_mbx, vha, 0x119a,
		    "Unable to verify login-state (%x/%x) for loop_id %x.\n",
		    current_login_state, last_login_state, fcport->loop_id);
		rval = QLA_FUNCTION_FAILED;
		goto gpd_error_out;
	}

	if (fcport->loop_id == FC_NO_LOOP_ID ||
	    (memcmp(fcport->port_name, (uint8_t *)&zero, 8) &&
	     memcmp(fcport->port_name, pd->port_name, 8))) {
		/* We lost the device mid way. */
		rval = QLA_NOT_LOGGED_IN;
		goto gpd_error_out;
	}

	/* Names are little-endian. */
	memcpy(fcport->node_name, pd->node_name, WWN_SIZE);
	memcpy(fcport->port_name, pd->port_name, WWN_SIZE);

	/* Get port_id of device. */
	fcport->d_id.b.domain = pd->port_id[0];
	fcport->d_id.b.area = pd->port_id[1];
	fcport->d_id.b.al_pa = pd->port_id[2];
	fcport->d_id.b.rsvd_1 = 0;

	if (fcport->fc4f_nvme) {
		fcport->port_type = 0;
		if ((pd->prli_svc_param_word_3[0] & BIT_5) == 0)
			fcport->port_type |= FCT_NVME_INITIATOR;
		if ((pd->prli_svc_param_word_3[0] & BIT_4) == 0)
			fcport->port_type |= FCT_NVME_TARGET;
		if ((pd->prli_svc_param_word_3[0] & BIT_3) == 0)
			fcport->port_type |= FCT_NVME_DISCOVERY;
	} else {
		/* If not target must be initiator or unknown type. */
		if ((pd->prli_svc_param_word_3[0] & BIT_4) == 0)
			fcport->port_type = FCT_INITIATOR;
		else
			fcport->port_type = FCT_TARGET;
	}
	/* Passback COS information. */
	fcport->supported_classes = (pd->flags & PDF_CLASS_2) ?
		FC_COS_CLASS2 : FC_COS_CLASS3;

	if (pd->prli_svc_param_word_3[0] & BIT_7) {
		fcport->flags |= FCF_CONF_COMP_SUPPORTED;
		fcport->conf_compl_supported = 1;
	}

gpd_error_out:
	return rval;
}