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
struct qcom_smd_edge {int /*<<< orphan*/  ipc_bit; int /*<<< orphan*/  ipc_offset; int /*<<< orphan*/  ipc_regmap; scalar_t__ mbox_chan; } ;
struct qcom_smd_channel {struct qcom_smd_edge* edge; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_client_txdone (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_send_message (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void qcom_smd_signal_channel(struct qcom_smd_channel *channel)
{
	struct qcom_smd_edge *edge = channel->edge;

	if (edge->mbox_chan) {
		/*
		 * We can ignore a failing mbox_send_message() as the only
		 * possible cause is that the FIFO in the framework is full of
		 * other writes to the same bit.
		 */
		mbox_send_message(edge->mbox_chan, NULL);
		mbox_client_txdone(edge->mbox_chan, 0);
	} else {
		regmap_write(edge->ipc_regmap, edge->ipc_offset, BIT(edge->ipc_bit));
	}
}