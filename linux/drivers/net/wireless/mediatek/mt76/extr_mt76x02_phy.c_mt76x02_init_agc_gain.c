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
struct TYPE_2__ {int low_gain; int gain_init_done; void** agc_gain_init; int /*<<< orphan*/  agc_gain_cur; } ;
struct mt76x02_dev {TYPE_1__ cal; } ;

/* Variables and functions */
 int /*<<< orphan*/  AGC ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_BBP_AGC_GAIN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void**,int) ; 
 void* mt76_get_field (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mt76x02_init_agc_gain(struct mt76x02_dev *dev)
{
	dev->cal.agc_gain_init[0] = mt76_get_field(dev, MT_BBP(AGC, 8),
						   MT_BBP_AGC_GAIN);
	dev->cal.agc_gain_init[1] = mt76_get_field(dev, MT_BBP(AGC, 9),
						   MT_BBP_AGC_GAIN);
	memcpy(dev->cal.agc_gain_cur, dev->cal.agc_gain_init,
	       sizeof(dev->cal.agc_gain_cur));
	dev->cal.low_gain = -1;
	dev->cal.gain_init_done = true;
}