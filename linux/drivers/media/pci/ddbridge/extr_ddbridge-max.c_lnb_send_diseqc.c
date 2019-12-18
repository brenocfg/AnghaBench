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
typedef  int u32 ;
struct dvb_diseqc_master_cmd {int msg_len; int /*<<< orphan*/ * msg; } ;
struct ddb {int dummy; } ;

/* Variables and functions */
 int DDB_LINK_TAG (int) ; 
 int LNB_BUF_LEVEL (int) ; 
 int LNB_BUF_WRITE (int) ; 
 int /*<<< orphan*/  LNB_CMD_DISEQC ; 
 int /*<<< orphan*/  ddbwritel (struct ddb*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lnb_command (struct ddb*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lnb_send_diseqc(struct ddb *dev, u32 link, u32 input,
			   struct dvb_diseqc_master_cmd *cmd)
{
	u32 tag = DDB_LINK_TAG(link);
	int i;

	ddbwritel(dev, 0, tag | LNB_BUF_LEVEL(input));
	for (i = 0; i < cmd->msg_len; i++)
		ddbwritel(dev, cmd->msg[i], tag | LNB_BUF_WRITE(input));
	lnb_command(dev, link, input, LNB_CMD_DISEQC);
	return 0;
}