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
struct qcom_smp2p {int /*<<< orphan*/  ipc_bit; int /*<<< orphan*/  ipc_offset; int /*<<< orphan*/  ipc_regmap; scalar_t__ mbox_chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_client_txdone (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbox_send_message (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void qcom_smp2p_kick(struct qcom_smp2p *smp2p)
{
	/* Make sure any updated data is written before the kick */
	wmb();

	if (smp2p->mbox_chan) {
		mbox_send_message(smp2p->mbox_chan, NULL);
		mbox_client_txdone(smp2p->mbox_chan, 0);
	} else {
		regmap_write(smp2p->ipc_regmap, smp2p->ipc_offset, BIT(smp2p->ipc_bit));
	}
}