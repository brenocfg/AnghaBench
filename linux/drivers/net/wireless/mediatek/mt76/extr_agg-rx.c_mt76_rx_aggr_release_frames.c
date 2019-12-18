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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff_head {int dummy; } ;
struct mt76_rx_tid {int head; int size; } ;

/* Variables and functions */
 scalar_t__ ieee80211_sn_less (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_aggr_release (struct mt76_rx_tid*,struct sk_buff_head*,int) ; 

__attribute__((used)) static void
mt76_rx_aggr_release_frames(struct mt76_rx_tid *tid,
			    struct sk_buff_head *frames,
			    u16 head)
{
	int idx;

	while (ieee80211_sn_less(tid->head, head)) {
		idx = tid->head % tid->size;
		mt76_aggr_release(tid, frames, idx);
	}
}