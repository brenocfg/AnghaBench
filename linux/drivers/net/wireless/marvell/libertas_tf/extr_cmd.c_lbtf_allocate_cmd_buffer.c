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
struct lbtf_private {struct cmd_ctrl_node* cmd_array; } ;
struct cmd_ctrl_node {int /*<<< orphan*/  cmdwait_q; void* cmdbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int LBS_CMD_BUFFER_SIZE ; 
 int LBS_NUM_CMD_BUFFERS ; 
 int /*<<< orphan*/  LBTF_DEB_HOST ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_cleanup_and_insert_cmd (struct lbtf_private*,struct cmd_ctrl_node*) ; 
 int /*<<< orphan*/  lbtf_deb_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lbtf_deb_host (char*) ; 
 int /*<<< orphan*/  lbtf_deb_leave_args (int /*<<< orphan*/ ,char*,int) ; 

int lbtf_allocate_cmd_buffer(struct lbtf_private *priv)
{
	int ret = 0;
	u32 bufsize;
	u32 i;
	struct cmd_ctrl_node *cmdarray;

	lbtf_deb_enter(LBTF_DEB_HOST);

	/* Allocate and initialize the command array */
	bufsize = sizeof(struct cmd_ctrl_node) * LBS_NUM_CMD_BUFFERS;
	cmdarray = kzalloc(bufsize, GFP_KERNEL);
	if (!cmdarray) {
		lbtf_deb_host("ALLOC_CMD_BUF: tempcmd_array is NULL\n");
		ret = -1;
		goto done;
	}
	priv->cmd_array = cmdarray;

	/* Allocate and initialize each command buffer in the command array */
	for (i = 0; i < LBS_NUM_CMD_BUFFERS; i++) {
		cmdarray[i].cmdbuf = kzalloc(LBS_CMD_BUFFER_SIZE, GFP_KERNEL);
		if (!cmdarray[i].cmdbuf) {
			lbtf_deb_host("ALLOC_CMD_BUF: ptempvirtualaddr is NULL\n");
			ret = -1;
			goto done;
		}
	}

	for (i = 0; i < LBS_NUM_CMD_BUFFERS; i++) {
		init_waitqueue_head(&cmdarray[i].cmdwait_q);
		lbtf_cleanup_and_insert_cmd(priv, &cmdarray[i]);
	}

	ret = 0;

done:
	lbtf_deb_leave_args(LBTF_DEB_HOST, "ret %d", ret);
	return ret;
}