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
struct TYPE_3__ {int /*<<< orphan*/ * high_gain; } ;
struct TYPE_4__ {TYPE_1__ rx; } ;
struct mt76x02_dev {TYPE_2__ cal; } ;
typedef  int /*<<< orphan*/  s8 ;

/* Variables and functions */
 int /*<<< orphan*/  mt76x2_adjust_agc_gain (struct mt76x02_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x2_adjust_high_lna_gain (struct mt76x02_dev*,int,int /*<<< orphan*/ ) ; 

void mt76x2_apply_gain_adj(struct mt76x02_dev *dev)
{
	s8 *gain_adj = dev->cal.rx.high_gain;

	mt76x2_adjust_high_lna_gain(dev, 4, gain_adj[0]);
	mt76x2_adjust_high_lna_gain(dev, 5, gain_adj[1]);

	mt76x2_adjust_agc_gain(dev, 8, gain_adj[0]);
	mt76x2_adjust_agc_gain(dev, 9, gain_adj[1]);
}