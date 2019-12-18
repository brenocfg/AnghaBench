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
typedef  int u32 ;
struct TYPE_4__ {int* start; int size; int /*<<< orphan*/  idx; } ;
struct tiger_hw {TYPE_2__ send; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int nr; struct tiger_hw* hw; } ;
struct tiger_ch {TYPE_1__ bch; } ;

/* Variables and functions */
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fill_mem(struct tiger_ch *bc, u32 idx, u32 cnt, u32 fill)
{
	struct tiger_hw *card = bc->bch.hw;
	u32 mask = 0xff, val;

	pr_debug("%s: B%1d fill %02x len %d idx %d/%d\n", card->name,
		 bc->bch.nr, fill, cnt, idx, card->send.idx);
	if (bc->bch.nr & 2) {
		fill  <<= 8;
		mask <<= 8;
	}
	mask ^= 0xffffffff;
	while (cnt--) {
		val = card->send.start[idx];
		val &= mask;
		val |= fill;
		card->send.start[idx++] = val;
		if (idx >= card->send.size)
			idx = 0;
	}
}