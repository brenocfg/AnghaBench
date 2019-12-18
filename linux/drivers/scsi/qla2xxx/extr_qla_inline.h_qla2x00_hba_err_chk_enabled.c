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
typedef  int /*<<< orphan*/  srb_t ;

/* Variables and functions */
 int /*<<< orphan*/  GET_CMD_SP (int /*<<< orphan*/ *) ; 
#define  SCSI_PROT_READ_INSERT 133 
#define  SCSI_PROT_READ_PASS 132 
#define  SCSI_PROT_READ_STRIP 131 
#define  SCSI_PROT_WRITE_INSERT 130 
#define  SCSI_PROT_WRITE_PASS 129 
#define  SCSI_PROT_WRITE_STRIP 128 
 int ql2xenablehba_err_chk ; 
 int scsi_get_prot_op (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int
qla2x00_hba_err_chk_enabled(srb_t *sp)
{
	/*
	 * Uncomment when corresponding SCSI changes are done.
	 *
	if (!sp->cmd->prot_chk)
		return 0;
	 *
	 */
	switch (scsi_get_prot_op(GET_CMD_SP(sp))) {
	case SCSI_PROT_READ_STRIP:
	case SCSI_PROT_WRITE_INSERT:
		if (ql2xenablehba_err_chk >= 1)
			return 1;
		break;
	case SCSI_PROT_READ_PASS:
	case SCSI_PROT_WRITE_PASS:
		if (ql2xenablehba_err_chk >= 2)
			return 1;
		break;
	case SCSI_PROT_READ_INSERT:
	case SCSI_PROT_WRITE_STRIP:
		return 1;
	}
	return 0;
}