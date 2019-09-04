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
struct tegra_bpmp_mb_data {int code; int /*<<< orphan*/  data; } ;
struct tegra_bpmp_channel {int /*<<< orphan*/  ivc; struct tegra_bpmp* bpmp; TYPE_1__* ib; } ;
struct TYPE_4__ {int /*<<< orphan*/  channel; } ;
struct tegra_bpmp {TYPE_2__ mbox; } ;
struct TYPE_3__ {unsigned long flags; } ;

/* Variables and functions */
 int IS_ERR (struct tegra_bpmp_mb_data*) ; 
 unsigned long MSG_ACK ; 
 size_t MSG_DATA_MIN_SZ ; 
 unsigned long MSG_RING ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  mbox_client_txdone (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mbox_send_message (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 int tegra_ivc_read_advance (int /*<<< orphan*/ ) ; 
 int tegra_ivc_write_advance (int /*<<< orphan*/ ) ; 
 struct tegra_bpmp_mb_data* tegra_ivc_write_get_next_frame (int /*<<< orphan*/ ) ; 

void tegra_bpmp_mrq_return(struct tegra_bpmp_channel *channel, int code,
			   const void *data, size_t size)
{
	unsigned long flags = channel->ib->flags;
	struct tegra_bpmp *bpmp = channel->bpmp;
	struct tegra_bpmp_mb_data *frame;
	int err;

	if (WARN_ON(size > MSG_DATA_MIN_SZ))
		return;

	err = tegra_ivc_read_advance(channel->ivc);
	if (WARN_ON(err < 0))
		return;

	if ((flags & MSG_ACK) == 0)
		return;

	frame = tegra_ivc_write_get_next_frame(channel->ivc);
	if (WARN_ON(IS_ERR(frame)))
		return;

	frame->code = code;

	if (data && size > 0)
		memcpy(frame->data, data, size);

	err = tegra_ivc_write_advance(channel->ivc);
	if (WARN_ON(err < 0))
		return;

	if (flags & MSG_RING) {
		err = mbox_send_message(bpmp->mbox.channel, NULL);
		if (WARN_ON(err < 0))
			return;

		mbox_client_txdone(bpmp->mbox.channel, 0);
	}
}