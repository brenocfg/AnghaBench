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
struct mt7601u_rate_power {TYPE_2__* ht; TYPE_2__* ofdm; TYPE_2__* cck; } ;
struct mt7601u_dev {TYPE_1__* ee; } ;
typedef  int /*<<< orphan*/  s8 ;
struct TYPE_4__ {int /*<<< orphan*/  bw20; } ;
struct TYPE_3__ {int /*<<< orphan*/ * real_cck_bw20; struct mt7601u_rate_power power_rate_table; } ;

/* Variables and functions */
 int /*<<< orphan*/  mt7601u_set_power_rate (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
mt7601u_save_power_rate(struct mt7601u_dev *dev, s8 delta, u32 val, int i)
{
	struct mt7601u_rate_power *t = &dev->ee->power_rate_table;

	switch (i) {
	case 0:
		mt7601u_set_power_rate(&t->cck[0], delta, (val >> 0) & 0xff);
		mt7601u_set_power_rate(&t->cck[1], delta, (val >> 8) & 0xff);
		/* Save cck bw20 for fixups of channel 14 */
		dev->ee->real_cck_bw20[0] = t->cck[0].bw20;
		dev->ee->real_cck_bw20[1] = t->cck[1].bw20;

		mt7601u_set_power_rate(&t->ofdm[0], delta, (val >> 16) & 0xff);
		mt7601u_set_power_rate(&t->ofdm[1], delta, (val >> 24) & 0xff);
		break;
	case 1:
		mt7601u_set_power_rate(&t->ofdm[2], delta, (val >> 0) & 0xff);
		mt7601u_set_power_rate(&t->ofdm[3], delta, (val >> 8) & 0xff);
		mt7601u_set_power_rate(&t->ht[0], delta, (val >> 16) & 0xff);
		mt7601u_set_power_rate(&t->ht[1], delta, (val >> 24) & 0xff);
		break;
	case 2:
		mt7601u_set_power_rate(&t->ht[2], delta, (val >> 0) & 0xff);
		mt7601u_set_power_rate(&t->ht[3], delta, (val >> 8) & 0xff);
		break;
	}
}