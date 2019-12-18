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
struct scsi_cmnd {unsigned int cmd_len; int* cmnd; } ;
struct qlogicfas408_priv {int qbase; int int_type; int qinitid; struct scsi_cmnd* qlcmd; scalar_t__ qabort; } ;

/* Variables and functions */
 int /*<<< orphan*/  REG0 ; 
 int /*<<< orphan*/  REG1 ; 
 struct qlogicfas408_priv* get_priv_by_cmd (struct scsi_cmnd*) ; 
 int inb (int) ; 
 int /*<<< orphan*/  outb (int,int) ; 
 int qlcfg5 ; 
 int qlcfg6 ; 
 int qlcfg7 ; 
 int qlcfg8 ; 
 int qlcfg9 ; 
 int qlcfgc ; 
 int scmd_id (struct scsi_cmnd*) ; 

__attribute__((used)) static void ql_icmd(struct scsi_cmnd *cmd)
{
	struct qlogicfas408_priv *priv = get_priv_by_cmd(cmd);
	int 	qbase = priv->qbase;
	int	int_type = priv->int_type;
	unsigned int i;

	priv->qabort = 0;

	REG0;
	/* clearing of interrupts and the fifo is needed */

	inb(qbase + 5);		/* clear interrupts */
	if (inb(qbase + 5))	/* if still interrupting */
		outb(2, qbase + 3);	/* reset chip */
	else if (inb(qbase + 7) & 0x1f)
		outb(1, qbase + 3);	/* clear fifo */
	while (inb(qbase + 5));	/* clear ints */
	REG1;
	outb(1, qbase + 8);	/* set for PIO pseudo DMA */
	outb(0, qbase + 0xb);	/* disable ints */
	inb(qbase + 8);		/* clear int bits */
	REG0;
	outb(0x40, qbase + 0xb);	/* enable features */

	/* configurables */
	outb(qlcfgc, qbase + 0xc);
	/* config: no reset interrupt, (initiator) bus id */
	outb(0x40 | qlcfg8 | priv->qinitid, qbase + 8);
	outb(qlcfg7, qbase + 7);
	outb(qlcfg6, qbase + 6);
	outb(qlcfg5, qbase + 5);	/* select timer */
	outb(qlcfg9 & 7, qbase + 9);	/* prescaler */
/*	outb(0x99, qbase + 5);	*/
	outb(scmd_id(cmd), qbase + 4);

	for (i = 0; i < cmd->cmd_len; i++)
		outb(cmd->cmnd[i], qbase + 2);

	priv->qlcmd = cmd;
	outb(0x41, qbase + 3);	/* select and send command */
}