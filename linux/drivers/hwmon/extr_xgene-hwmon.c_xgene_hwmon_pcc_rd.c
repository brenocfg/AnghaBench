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
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int msg; int param1; int param2; } ;
struct xgene_hwmon_dev {int resp_pending; int mbox_idx; int /*<<< orphan*/  rd_mutex; int /*<<< orphan*/  mbox_chan; TYPE_1__ sync_msg; int /*<<< orphan*/  dev; int /*<<< orphan*/  usecs_lat; int /*<<< orphan*/  rd_complete; struct acpi_pcct_shared_memory* pcc_comm_addr; } ;
struct slimpro_resp_msg {int dummy; } ;
struct acpi_pcct_shared_memory {int signature; int command; int status; } ;

/* Variables and functions */
 int EINVAL ; 
 int ETIMEDOUT ; 
 int MSG_TYPE (int) ; 
 int MSG_TYPE_ERR ; 
 int PCCC_GENERATE_DB_INT ; 
 int PCCS_CMD_COMPLETE ; 
 int PCC_SIGNATURE_MASK ; 
 int /*<<< orphan*/  READ_ONCE (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_le16 (int) ; 
 int /*<<< orphan*/  cpu_to_le32 (int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_chan_txdone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mbox_send_message (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_completion_timeout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xgene_hwmon_pcc_rd(struct xgene_hwmon_dev *ctx, u32 *msg)
{
	struct acpi_pcct_shared_memory *generic_comm_base = ctx->pcc_comm_addr;
	u32 *ptr = (void *)(generic_comm_base + 1);
	int rc, i;
	u16 val;

	mutex_lock(&ctx->rd_mutex);
	init_completion(&ctx->rd_complete);
	ctx->resp_pending = true;

	/* Write signature for subspace */
	WRITE_ONCE(generic_comm_base->signature,
		   cpu_to_le32(PCC_SIGNATURE_MASK | ctx->mbox_idx));

	/* Write to the shared command region */
	WRITE_ONCE(generic_comm_base->command,
		   cpu_to_le16(MSG_TYPE(msg[0]) | PCCC_GENERATE_DB_INT));

	/* Flip CMD COMPLETE bit */
	val = le16_to_cpu(READ_ONCE(generic_comm_base->status));
	val &= ~PCCS_CMD_COMPLETE;
	WRITE_ONCE(generic_comm_base->status, cpu_to_le16(val));

	/* Copy the message to the PCC comm space */
	for (i = 0; i < sizeof(struct slimpro_resp_msg) / 4; i++)
		WRITE_ONCE(ptr[i], cpu_to_le32(msg[i]));

	/* Ring the doorbell */
	rc = mbox_send_message(ctx->mbox_chan, msg);
	if (rc < 0) {
		dev_err(ctx->dev, "Mailbox send error %d\n", rc);
		goto err;
	}
	if (!wait_for_completion_timeout(&ctx->rd_complete,
					 usecs_to_jiffies(ctx->usecs_lat))) {
		dev_err(ctx->dev, "Mailbox operation timed out\n");
		rc = -ETIMEDOUT;
		goto err;
	}

	/* Check for error message */
	if (MSG_TYPE(ctx->sync_msg.msg) == MSG_TYPE_ERR) {
		rc = -EINVAL;
		goto err;
	}

	msg[0] = ctx->sync_msg.msg;
	msg[1] = ctx->sync_msg.param1;
	msg[2] = ctx->sync_msg.param2;

err:
	mbox_chan_txdone(ctx->mbox_chan, 0);
	ctx->resp_pending = false;
	mutex_unlock(&ctx->rd_mutex);
	return rc;
}