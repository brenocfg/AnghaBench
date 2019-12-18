#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct Scsi_Host {int dummy; } ;
struct TYPE_4__ {int phase; } ;
struct TYPE_5__ {TYPE_1__ SCp; } ;

/* Variables and functions */
 unsigned int BUSFREE ; 
 TYPE_2__* CURRENT_SC ; 
 int GETPORT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KERN_INFO ; 
 scalar_t__ LASTSTATE ; 
 scalar_t__ PREVSTATE ; 
#define  P_CMD 133 
#define  P_DATAI 132 
#define  P_DATAO 131 
 int P_MASK ; 
#define  P_MSGI 130 
#define  P_MSGO 129 
#define  P_STATUS 128 
 unsigned int REQINIT ; 
 unsigned int SCSIPERR ; 
 unsigned int SCSIRSTI ; 
 int /*<<< orphan*/  SCSISEQ ; 
 int /*<<< orphan*/  SCSISIG ; 
 unsigned int SELDI ; 
 unsigned int SELDO ; 
 unsigned int SELTO ; 
 int /*<<< orphan*/  SETPORT (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  SSTAT0 ; 
 int /*<<< orphan*/  SSTAT1 ; 
 scalar_t__ STATE ; 
 scalar_t__ busfree ; 
 scalar_t__ cmd ; 
 scalar_t__ datai ; 
 scalar_t__ datao ; 
 scalar_t__ msgi ; 
 scalar_t__ msgo ; 
 scalar_t__ parerr ; 
 scalar_t__ rsti ; 
 int /*<<< orphan*/  scmd_printk (int /*<<< orphan*/ ,TYPE_2__*,char*) ; 
 scalar_t__ seldi ; 
 scalar_t__ seldo ; 
 int selecting ; 
 scalar_t__ selto ; 
 scalar_t__ status ; 
 scalar_t__ unknown ; 

__attribute__((used)) static int update_state(struct Scsi_Host *shpnt)
{
	int dataphase=0;
	unsigned int stat0 = GETPORT(SSTAT0);
	unsigned int stat1 = GETPORT(SSTAT1);

	PREVSTATE = STATE;
	STATE=unknown;

	if(stat1 & SCSIRSTI) {
		STATE=rsti;
		SETPORT(SCSISEQ,0);
		SETPORT(SSTAT1,SCSIRSTI);
	} else if (stat0 & SELDI && PREVSTATE == busfree) {
		STATE=seldi;
	} else if(stat0 & SELDO && CURRENT_SC && (CURRENT_SC->SCp.phase & selecting)) {
		STATE=seldo;
	} else if(stat1 & SELTO) {
		STATE=selto;
	} else if(stat1 & BUSFREE) {
		STATE=busfree;
		SETPORT(SSTAT1,BUSFREE);
	} else if(stat1 & SCSIPERR) {
		STATE=parerr;
		SETPORT(SSTAT1,SCSIPERR);
	} else if(stat1 & REQINIT) {
		switch(GETPORT(SCSISIG) & P_MASK) {
		case P_MSGI:	STATE=msgi;	break;
		case P_MSGO:	STATE=msgo;	break;
		case P_DATAO:	STATE=datao;	break;
		case P_DATAI:	STATE=datai;	break;
		case P_STATUS:	STATE=status;	break;
		case P_CMD:	STATE=cmd;	break;
		}
		dataphase=1;
	}

	if((stat0 & SELDI) && STATE!=seldi && !dataphase) {
		scmd_printk(KERN_INFO, CURRENT_SC, "reselection missed?");
	}

	if(STATE!=PREVSTATE) {
		LASTSTATE=PREVSTATE;
	}

	return dataphase;
}