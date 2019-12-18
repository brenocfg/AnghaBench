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
typedef  int u8 ;
struct se_session {int sup_prot_ops; scalar_t__ sess_prot_type; } ;
struct TYPE_2__ {int emulate_rest_reord; int emulate_ua_intlck_ctrl; scalar_t__ pi_prot_type; scalar_t__ emulate_tas; } ;
struct se_device {TYPE_1__ dev_attrib; } ;
struct se_cmd {struct se_session* se_sess; struct se_device* se_dev; } ;

/* Variables and functions */
 int TARGET_PROT_DIN_PASS ; 
 int TARGET_PROT_DOUT_PASS ; 
 scalar_t__ target_sense_desc_format (struct se_device*) ; 

__attribute__((used)) static int spc_modesense_control(struct se_cmd *cmd, u8 pc, u8 *p)
{
	struct se_device *dev = cmd->se_dev;
	struct se_session *sess = cmd->se_sess;

	p[0] = 0x0a;
	p[1] = 0x0a;

	/* No changeable values for now */
	if (pc == 1)
		goto out;

	/* GLTSD: No implicit save of log parameters */
	p[2] = (1 << 1);
	if (target_sense_desc_format(dev))
		/* D_SENSE: Descriptor format sense data for 64bit sectors */
		p[2] |= (1 << 2);

	/*
	 * From spc4r23, 7.4.7 Control mode page
	 *
	 * The QUEUE ALGORITHM MODIFIER field (see table 368) specifies
	 * restrictions on the algorithm used for reordering commands
	 * having the SIMPLE task attribute (see SAM-4).
	 *
	 *                    Table 368 -- QUEUE ALGORITHM MODIFIER field
	 *                         Code      Description
	 *                          0h       Restricted reordering
	 *                          1h       Unrestricted reordering allowed
	 *                          2h to 7h    Reserved
	 *                          8h to Fh    Vendor specific
	 *
	 * A value of zero in the QUEUE ALGORITHM MODIFIER field specifies that
	 * the device server shall order the processing sequence of commands
	 * having the SIMPLE task attribute such that data integrity is maintained
	 * for that I_T nexus (i.e., if the transmission of new SCSI transport protocol
	 * requests is halted at any time, the final value of all data observable
	 * on the medium shall be the same as if all the commands had been processed
	 * with the ORDERED task attribute).
	 *
	 * A value of one in the QUEUE ALGORITHM MODIFIER field specifies that the
	 * device server may reorder the processing sequence of commands having the
	 * SIMPLE task attribute in any manner. Any data integrity exposures related to
	 * command sequence order shall be explicitly handled by the application client
	 * through the selection of appropriate ommands and task attributes.
	 */
	p[3] = (dev->dev_attrib.emulate_rest_reord == 1) ? 0x00 : 0x10;
	/*
	 * From spc4r17, section 7.4.6 Control mode Page
	 *
	 * Unit Attention interlocks control (UN_INTLCK_CTRL) to code 00b
	 *
	 * 00b: The logical unit shall clear any unit attention condition
	 * reported in the same I_T_L_Q nexus transaction as a CHECK CONDITION
	 * status and shall not establish a unit attention condition when a com-
	 * mand is completed with BUSY, TASK SET FULL, or RESERVATION CONFLICT
	 * status.
	 *
	 * 10b: The logical unit shall not clear any unit attention condition
	 * reported in the same I_T_L_Q nexus transaction as a CHECK CONDITION
	 * status and shall not establish a unit attention condition when
	 * a command is completed with BUSY, TASK SET FULL, or RESERVATION
	 * CONFLICT status.
	 *
	 * 11b a The logical unit shall not clear any unit attention condition
	 * reported in the same I_T_L_Q nexus transaction as a CHECK CONDITION
	 * status and shall establish a unit attention condition for the
	 * initiator port associated with the I_T nexus on which the BUSY,
	 * TASK SET FULL, or RESERVATION CONFLICT status is being returned.
	 * Depending on the status, the additional sense code shall be set to
	 * PREVIOUS BUSY STATUS, PREVIOUS TASK SET FULL STATUS, or PREVIOUS
	 * RESERVATION CONFLICT STATUS. Until it is cleared by a REQUEST SENSE
	 * command, a unit attention condition shall be established only once
	 * for a BUSY, TASK SET FULL, or RESERVATION CONFLICT status regardless
	 * to the number of commands completed with one of those status codes.
	 */
	p[4] = (dev->dev_attrib.emulate_ua_intlck_ctrl == 2) ? 0x30 :
	       (dev->dev_attrib.emulate_ua_intlck_ctrl == 1) ? 0x20 : 0x00;
	/*
	 * From spc4r17, section 7.4.6 Control mode Page
	 *
	 * Task Aborted Status (TAS) bit set to zero.
	 *
	 * A task aborted status (TAS) bit set to zero specifies that aborted
	 * tasks shall be terminated by the device server without any response
	 * to the application client. A TAS bit set to one specifies that tasks
	 * aborted by the actions of an I_T nexus other than the I_T nexus on
	 * which the command was received shall be completed with TASK ABORTED
	 * status (see SAM-4).
	 */
	p[5] = (dev->dev_attrib.emulate_tas) ? 0x40 : 0x00;
	/*
	 * From spc4r30, section 7.5.7 Control mode page
	 *
	 * Application Tag Owner (ATO) bit set to one.
	 *
	 * If the ATO bit is set to one the device server shall not modify the
	 * LOGICAL BLOCK APPLICATION TAG field and, depending on the protection
	 * type, shall not modify the contents of the LOGICAL BLOCK REFERENCE
	 * TAG field.
	 */
	if (sess->sup_prot_ops & (TARGET_PROT_DIN_PASS | TARGET_PROT_DOUT_PASS)) {
		if (dev->dev_attrib.pi_prot_type || sess->sess_prot_type)
			p[5] |= 0x80;
	}

	p[8] = 0xff;
	p[9] = 0xff;
	p[11] = 30;

out:
	return 12;
}