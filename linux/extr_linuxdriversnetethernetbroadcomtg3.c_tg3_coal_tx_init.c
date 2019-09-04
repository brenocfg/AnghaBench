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
typedef  scalar_t__ u32 ;
struct tg3 {int txq_cnt; int irq_max; } ;
struct ethtool_coalesce {int /*<<< orphan*/  tx_max_coalesced_frames_irq; int /*<<< orphan*/  tx_max_coalesced_frames; int /*<<< orphan*/  tx_coalesce_usecs; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE_TSS ; 
 scalar_t__ HOSTCC_TXCOAL_MAXF_INT ; 
 scalar_t__ HOSTCC_TXCOAL_MAXF_INT_VEC1 ; 
 scalar_t__ HOSTCC_TXCOL_TICKS ; 
 scalar_t__ HOSTCC_TXCOL_TICKS_VEC1 ; 
 scalar_t__ HOSTCC_TXMAX_FRAMES ; 
 scalar_t__ HOSTCC_TXMAX_FRAMES_VEC1 ; 
 int /*<<< orphan*/  tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tw32 (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_coal_tx_init(struct tg3 *tp, struct ethtool_coalesce *ec)
{
	int i = 0;

	if (!tg3_flag(tp, ENABLE_TSS)) {
		tw32(HOSTCC_TXCOL_TICKS, ec->tx_coalesce_usecs);
		tw32(HOSTCC_TXMAX_FRAMES, ec->tx_max_coalesced_frames);
		tw32(HOSTCC_TXCOAL_MAXF_INT, ec->tx_max_coalesced_frames_irq);
	} else {
		tw32(HOSTCC_TXCOL_TICKS, 0);
		tw32(HOSTCC_TXMAX_FRAMES, 0);
		tw32(HOSTCC_TXCOAL_MAXF_INT, 0);

		for (; i < tp->txq_cnt; i++) {
			u32 reg;

			reg = HOSTCC_TXCOL_TICKS_VEC1 + i * 0x18;
			tw32(reg, ec->tx_coalesce_usecs);
			reg = HOSTCC_TXMAX_FRAMES_VEC1 + i * 0x18;
			tw32(reg, ec->tx_max_coalesced_frames);
			reg = HOSTCC_TXCOAL_MAXF_INT_VEC1 + i * 0x18;
			tw32(reg, ec->tx_max_coalesced_frames_irq);
		}
	}

	for (; i < tp->irq_max - 1; i++) {
		tw32(HOSTCC_TXCOL_TICKS_VEC1 + i * 0x18, 0);
		tw32(HOSTCC_TXMAX_FRAMES_VEC1 + i * 0x18, 0);
		tw32(HOSTCC_TXCOAL_MAXF_INT_VEC1 + i * 0x18, 0);
	}
}