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
struct nbd_cmd {int /*<<< orphan*/  lock; int /*<<< orphan*/  flags; } ;
struct blk_mq_queue_data {int /*<<< orphan*/  rq; } ;
struct blk_mq_hw_ctx {int /*<<< orphan*/  queue_num; } ;
typedef  int blk_status_t ;

/* Variables and functions */
 int BLK_STS_IOERR ; 
 int BLK_STS_OK ; 
 int /*<<< orphan*/  NBD_CMD_REQUEUED ; 
 struct nbd_cmd* blk_mq_rq_to_pdu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nbd_handle_cmd (struct nbd_cmd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static blk_status_t nbd_queue_rq(struct blk_mq_hw_ctx *hctx,
			const struct blk_mq_queue_data *bd)
{
	struct nbd_cmd *cmd = blk_mq_rq_to_pdu(bd->rq);
	int ret;

	/*
	 * Since we look at the bio's to send the request over the network we
	 * need to make sure the completion work doesn't mark this request done
	 * before we are done doing our send.  This keeps us from dereferencing
	 * freed data if we have particularly fast completions (ie we get the
	 * completion before we exit sock_xmit on the last bvec) or in the case
	 * that the server is misbehaving (or there was an error) before we're
	 * done sending everything over the wire.
	 */
	mutex_lock(&cmd->lock);
	clear_bit(NBD_CMD_REQUEUED, &cmd->flags);

	/* We can be called directly from the user space process, which means we
	 * could possibly have signals pending so our sendmsg will fail.  In
	 * this case we need to return that we are busy, otherwise error out as
	 * appropriate.
	 */
	ret = nbd_handle_cmd(cmd, hctx->queue_num);
	if (ret < 0)
		ret = BLK_STS_IOERR;
	else if (!ret)
		ret = BLK_STS_OK;
	mutex_unlock(&cmd->lock);

	return ret;
}