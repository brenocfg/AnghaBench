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
typedef  int /*<<< orphan*/  u32 ;
struct slimpro_i2c_dev {int /*<<< orphan*/  rd_complete; int /*<<< orphan*/ * resp_msg; struct acpi_pcct_shared_memory* pcc_comm_addr; } ;
struct mbox_client {int dummy; } ;
struct acpi_pcct_shared_memory {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCC_STS_CMD_COMPLETE ; 
 int /*<<< orphan*/  PCC_STS_SCI_DOORBELL ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct slimpro_i2c_dev* to_slimpro_i2c_dev (struct mbox_client*) ; 
 scalar_t__ xgene_word_tst_and_clr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void slimpro_i2c_pcc_rx_cb(struct mbox_client *cl, void *msg)
{
	struct slimpro_i2c_dev *ctx = to_slimpro_i2c_dev(cl);
	struct acpi_pcct_shared_memory *generic_comm_base = ctx->pcc_comm_addr;

	/* Check if platform sends interrupt */
	if (!xgene_word_tst_and_clr(&generic_comm_base->status,
				    PCC_STS_SCI_DOORBELL))
		return;

	if (xgene_word_tst_and_clr(&generic_comm_base->status,
				   PCC_STS_CMD_COMPLETE)) {
		msg = generic_comm_base + 1;

		/* Response message msg[1] contains the return value. */
		if (ctx->resp_msg)
			*ctx->resp_msg = ((u32 *)msg)[1];

		complete(&ctx->rd_complete);
	}
}