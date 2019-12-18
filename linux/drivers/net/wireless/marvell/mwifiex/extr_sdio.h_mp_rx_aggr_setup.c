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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct TYPE_2__ {int pkt_cnt; int start_port; int ports; scalar_t__* len_arr; int /*<<< orphan*/ ** skb_arr; int /*<<< orphan*/  buf_len; } ;
struct sdio_mmc_card {TYPE_1__ mpa_rx; scalar_t__ supports_sdio_new_mode; } ;

/* Variables and functions */

__attribute__((used)) static inline void mp_rx_aggr_setup(struct sdio_mmc_card *card,
				    u16 rx_len, u8 port)
{
	card->mpa_rx.buf_len += rx_len;

	if (!card->mpa_rx.pkt_cnt)
		card->mpa_rx.start_port = port;

	if (card->supports_sdio_new_mode) {
		card->mpa_rx.ports |= (1 << port);
	} else {
		if (card->mpa_rx.start_port <= port)
			card->mpa_rx.ports |= 1 << (card->mpa_rx.pkt_cnt);
		else
			card->mpa_rx.ports |= 1 << (card->mpa_rx.pkt_cnt + 1);
	}
	card->mpa_rx.skb_arr[card->mpa_rx.pkt_cnt] = NULL;
	card->mpa_rx.len_arr[card->mpa_rx.pkt_cnt] = rx_len;
	card->mpa_rx.pkt_cnt++;
}