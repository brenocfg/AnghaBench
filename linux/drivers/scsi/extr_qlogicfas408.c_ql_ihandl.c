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
struct scsi_cmnd {int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;int /*<<< orphan*/  result; } ;
struct qlogicfas408_priv {int qbase; struct scsi_cmnd* qlcmd; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG0 ; 
 struct qlogicfas408_priv* get_priv_by_host (struct Scsi_Host*) ; 
 int inb (int) ; 
 int /*<<< orphan*/  ql_pcmd (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static void ql_ihandl(void *dev_id)
{
	struct scsi_cmnd *icmd;
	struct Scsi_Host *host = dev_id;
	struct qlogicfas408_priv *priv = get_priv_by_host(host);
	int qbase = priv->qbase;
	REG0;

	if (!(inb(qbase + 4) & 0x80))	/* false alarm? */
		return;

	if (priv->qlcmd == NULL) {	/* no command to process? */
		int i;
		i = 16;
		while (i-- && inb(qbase + 5));	/* maybe also ql_zap() */
		return;
	}
	icmd = priv->qlcmd;
	icmd->result = ql_pcmd(icmd);
	priv->qlcmd = NULL;
	/*
	 *	If result is CHECK CONDITION done calls qcommand to request 
	 *	sense 
	 */
	(icmd->scsi_done) (icmd);
}