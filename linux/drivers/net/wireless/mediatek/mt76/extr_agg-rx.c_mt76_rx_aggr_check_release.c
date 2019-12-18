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
struct sk_buff_head {int dummy; } ;
struct sk_buff {scalar_t__ cb; } ;
struct mt76_rx_tid {int nframes; int head; int size; struct sk_buff** reorder_buf; } ;
struct mt76_rx_status {int /*<<< orphan*/  seqno; scalar_t__ reorder_time; } ;

/* Variables and functions */
 scalar_t__ REORDER_TIMEOUT ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  mt76_rx_aggr_release_frames (struct mt76_rx_tid*,struct sk_buff_head*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_rx_aggr_release_head (struct mt76_rx_tid*,struct sk_buff_head*) ; 
 int /*<<< orphan*/  time_after (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
mt76_rx_aggr_check_release(struct mt76_rx_tid *tid, struct sk_buff_head *frames)
{
	struct mt76_rx_status *status;
	struct sk_buff *skb;
	int start, idx, nframes;

	if (!tid->nframes)
		return;

	mt76_rx_aggr_release_head(tid, frames);

	start = tid->head % tid->size;
	nframes = tid->nframes;

	for (idx = (tid->head + 1) % tid->size;
	     idx != start && nframes;
	     idx = (idx + 1) % tid->size) {
		skb = tid->reorder_buf[idx];
		if (!skb)
			continue;

		nframes--;
		status = (struct mt76_rx_status *)skb->cb;
		if (!time_after(jiffies,
				status->reorder_time + REORDER_TIMEOUT))
			continue;

		mt76_rx_aggr_release_frames(tid, frames, status->seqno);
	}

	mt76_rx_aggr_release_head(tid, frames);
}