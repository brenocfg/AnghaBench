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
struct TYPE_3__ {int cstat; int dstat; } ;
struct TYPE_4__ {TYPE_1__ cmd; } ;
struct irb {TYPE_2__ scsw; scalar_t__ ecw; } ;
struct ccw_device {int dummy; } ;

/* Variables and functions */
 int DEV_STAT_UNIT_CHECK ; 
 int /*<<< orphan*/  LCS_DBF_TEXT (int,int /*<<< orphan*/ ,char*) ; 
 size_t LCS_SENSE_BYTE_0 ; 
 size_t LCS_SENSE_BYTE_1 ; 
 size_t LCS_SENSE_BYTE_2 ; 
 size_t LCS_SENSE_BYTE_3 ; 
 char LCS_SENSE_CMD_REJECT ; 
 char LCS_SENSE_RESETTING_EVENT ; 
 int SCHN_STAT_CHAIN_CHECK ; 
 int SCHN_STAT_CHN_CTRL_CHK ; 
 int SCHN_STAT_CHN_DATA_CHK ; 
 int SCHN_STAT_INTF_CTRL_CHK ; 
 int SCHN_STAT_PROG_CHECK ; 
 int SCHN_STAT_PROT_CHECK ; 
 int /*<<< orphan*/  trace ; 

__attribute__((used)) static int
lcs_get_problem(struct ccw_device *cdev, struct irb *irb)
{
	int dstat, cstat;
	char *sense;

	sense = (char *) irb->ecw;
	cstat = irb->scsw.cmd.cstat;
	dstat = irb->scsw.cmd.dstat;

	if (cstat & (SCHN_STAT_CHN_CTRL_CHK | SCHN_STAT_INTF_CTRL_CHK |
		     SCHN_STAT_CHN_DATA_CHK | SCHN_STAT_CHAIN_CHECK |
		     SCHN_STAT_PROT_CHECK   | SCHN_STAT_PROG_CHECK)) {
		LCS_DBF_TEXT(2, trace, "CGENCHK");
		return 1;
	}
	if (dstat & DEV_STAT_UNIT_CHECK) {
		if (sense[LCS_SENSE_BYTE_1] &
		    LCS_SENSE_RESETTING_EVENT) {
			LCS_DBF_TEXT(2, trace, "REVIND");
			return 1;
		}
		if (sense[LCS_SENSE_BYTE_0] &
		    LCS_SENSE_CMD_REJECT) {
			LCS_DBF_TEXT(2, trace, "CMDREJ");
			return 0;
		}
		if ((!sense[LCS_SENSE_BYTE_0]) &&
		    (!sense[LCS_SENSE_BYTE_1]) &&
		    (!sense[LCS_SENSE_BYTE_2]) &&
		    (!sense[LCS_SENSE_BYTE_3])) {
			LCS_DBF_TEXT(2, trace, "ZEROSEN");
			return 0;
		}
		LCS_DBF_TEXT(2, trace, "DGENCHK");
		return 1;
	}
	return 0;
}