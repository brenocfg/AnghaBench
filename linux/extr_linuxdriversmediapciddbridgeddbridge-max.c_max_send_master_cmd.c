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
typedef  int u32 ;
struct dvb_frontend {struct ddb_input* sec_priv; } ;
struct dvb_diseqc_master_cmd {int msg_len; int /*<<< orphan*/ * msg; } ;
struct ddb_port {size_t lnr; struct ddb_dvb* dvb; struct ddb* dev; } ;
struct ddb_input {int nr; struct ddb_port* port; } ;
struct ddb_dvb {int /*<<< orphan*/  input; int /*<<< orphan*/  (* diseqc_send_master_cmd ) (struct dvb_frontend*,struct dvb_diseqc_master_cmd*) ;} ;
struct ddb {TYPE_2__* link; } ;
struct TYPE_3__ {int fmode; int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {TYPE_1__ lnb; } ;

/* Variables and functions */
 int DDB_LINK_TAG (size_t) ; 
 int LNB_BUF_LEVEL (int /*<<< orphan*/ ) ; 
 int LNB_BUF_WRITE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LNB_CMD_DISEQC ; 
 int /*<<< orphan*/  ddbwritel (struct ddb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lnb_command (struct ddb*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct dvb_frontend*,struct dvb_diseqc_master_cmd*) ; 

__attribute__((used)) static int max_send_master_cmd(struct dvb_frontend *fe,
			       struct dvb_diseqc_master_cmd *cmd)
{
	struct ddb_input *input = fe->sec_priv;
	struct ddb_port *port = input->port;
	struct ddb *dev = port->dev;
	struct ddb_dvb *dvb = &port->dvb[input->nr & 1];
	u32 tag = DDB_LINK_TAG(port->lnr);
	int i;
	u32 fmode = dev->link[port->lnr].lnb.fmode;

	if (fmode == 2 || fmode == 1)
		return 0;
	if (dvb->diseqc_send_master_cmd)
		dvb->diseqc_send_master_cmd(fe, cmd);

	mutex_lock(&dev->link[port->lnr].lnb.lock);
	ddbwritel(dev, 0, tag | LNB_BUF_LEVEL(dvb->input));
	for (i = 0; i < cmd->msg_len; i++)
		ddbwritel(dev, cmd->msg[i], tag | LNB_BUF_WRITE(dvb->input));
	lnb_command(dev, port->lnr, dvb->input, LNB_CMD_DISEQC);
	mutex_unlock(&dev->link[port->lnr].lnb.lock);
	return 0;
}