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
struct TYPE_4__ {int /*<<< orphan*/  raw; } ;
struct il_rx_pkt {TYPE_2__ u; } ;
struct il_rx_buf {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_delta; int /*<<< orphan*/  delta_stats; int /*<<< orphan*/  accum_stats; } ;
struct il_priv {TYPE_1__ _3945; } ;
struct il3945_notif_stats {int dummy; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  D_RX (char*) ; 
 int UCODE_STATS_CLEAR_MSK ; 
 int /*<<< orphan*/  il3945_hdl_stats (struct il_priv*,struct il_rx_buf*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct il_rx_pkt* rxb_addr (struct il_rx_buf*) ; 

void
il3945_hdl_c_stats(struct il_priv *il, struct il_rx_buf *rxb)
{
	struct il_rx_pkt *pkt = rxb_addr(rxb);
	__le32 *flag = (__le32 *) &pkt->u.raw;

	if (le32_to_cpu(*flag) & UCODE_STATS_CLEAR_MSK) {
#ifdef CONFIG_IWLEGACY_DEBUGFS
		memset(&il->_3945.accum_stats, 0,
		       sizeof(struct il3945_notif_stats));
		memset(&il->_3945.delta_stats, 0,
		       sizeof(struct il3945_notif_stats));
		memset(&il->_3945.max_delta, 0,
		       sizeof(struct il3945_notif_stats));
#endif
		D_RX("Statistics have been cleared\n");
	}
	il3945_hdl_stats(il, rxb);
}