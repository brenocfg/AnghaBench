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
struct tg3_napi {int /*<<< orphan*/  rx_rcb_mapping; int /*<<< orphan*/  rx_rcb; } ;
struct tg3 {int irq_max; int rx_ret_ring_mask; struct tg3_napi* napi; } ;

/* Variables and functions */
 int BDINFO_FLAGS_MAXLEN_SHIFT ; 
 int /*<<< orphan*/  ENABLE_RSS ; 
 int /*<<< orphan*/  NIC_SRAM_RCV_RET_RCB ; 
 scalar_t__ TG3_BDINFO_SIZE ; 
 scalar_t__ tg3_flag (struct tg3*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tg3_set_bdinfo (struct tg3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void tg3_rx_ret_rcbs_init(struct tg3 *tp)
{
	int i = 0;
	u32 rxrcb = NIC_SRAM_RCV_RET_RCB;

	if (tg3_flag(tp, ENABLE_RSS))
		i++;

	for (; i < tp->irq_max; i++, rxrcb += TG3_BDINFO_SIZE) {
		struct tg3_napi *tnapi = &tp->napi[i];

		if (!tnapi->rx_rcb)
			continue;

		tg3_set_bdinfo(tp, rxrcb, tnapi->rx_rcb_mapping,
			       (tp->rx_ret_ring_mask + 1) <<
				BDINFO_FLAGS_MAXLEN_SHIFT, 0);
	}
}