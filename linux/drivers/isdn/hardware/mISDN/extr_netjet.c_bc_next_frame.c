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
struct TYPE_3__ {scalar_t__ tx_idx; int /*<<< orphan*/  Flags; TYPE_2__* tx_skb; } ;
struct tiger_ch {TYPE_1__ bch; } ;
struct TYPE_4__ {scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_FILLEMPTY ; 
 int /*<<< orphan*/  FLG_TX_EMPTY ; 
 int /*<<< orphan*/  dev_kfree_skb (TYPE_2__*) ; 
 int /*<<< orphan*/  fill_dma (struct tiger_ch*) ; 
 scalar_t__ get_next_bframe (TYPE_1__*) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
bc_next_frame(struct tiger_ch *bc)
{
	int ret = 1;

	if (bc->bch.tx_skb && bc->bch.tx_idx < bc->bch.tx_skb->len) {
		fill_dma(bc);
	} else {
		dev_kfree_skb(bc->bch.tx_skb);
		if (get_next_bframe(&bc->bch)) {
			fill_dma(bc);
			test_and_clear_bit(FLG_TX_EMPTY, &bc->bch.Flags);
		} else if (test_bit(FLG_TX_EMPTY, &bc->bch.Flags)) {
			fill_dma(bc);
		} else if (test_bit(FLG_FILLEMPTY, &bc->bch.Flags)) {
			test_and_set_bit(FLG_TX_EMPTY, &bc->bch.Flags);
			ret = 0;
		} else {
			ret = 0;
		}
	}
	return ret;
}