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
typedef  int u8 ;
struct mt76_tx_status {int pktid; int rate; int is_probe; int retry; } ;
struct mt7601u_dev {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void
mt7601u_tx_pktid_dec(struct mt7601u_dev *dev, struct mt76_tx_status *stat)
{
	u8 req_rate = stat->pktid;
	u8 eff_rate = stat->rate & 0x7;

	req_rate -= 1;

	if (req_rate > 7) {
		stat->is_probe = true;
		req_rate -= 8;

		/* Decide between MCS0 and MCS7 which share pktid 9 */
		if (!req_rate && eff_rate)
			req_rate = 7;
	}

	stat->retry = req_rate - eff_rate;
}