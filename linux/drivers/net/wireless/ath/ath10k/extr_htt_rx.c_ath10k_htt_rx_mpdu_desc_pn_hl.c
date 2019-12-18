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
union htt_rx_pn_t {int pn48; int pn24; } ;
typedef  int u64 ;
struct TYPE_2__ {int /*<<< orphan*/  pn_63_32; } ;
struct htt_hl_rx_desc {int /*<<< orphan*/  pn_31_0; TYPE_1__ u0; } ;

/* Variables and functions */
 int __le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ath10k_htt_rx_mpdu_desc_pn_hl(struct htt_hl_rx_desc *rx_desc,
					  union htt_rx_pn_t *pn,
					  int pn_len_bits)
{
	switch (pn_len_bits) {
	case 48:
		pn->pn48 = __le32_to_cpu(rx_desc->pn_31_0) +
			   ((u64)(__le32_to_cpu(rx_desc->u0.pn_63_32) & 0xFFFF) << 32);
		break;
	case 24:
		pn->pn24 = __le32_to_cpu(rx_desc->pn_31_0);
		break;
	};
}