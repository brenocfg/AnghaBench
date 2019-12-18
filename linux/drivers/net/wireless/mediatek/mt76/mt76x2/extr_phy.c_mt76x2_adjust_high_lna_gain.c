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
struct mt76x02_dev {int dummy; } ;
typedef  int s8 ;

/* Variables and functions */
 int /*<<< orphan*/  AGC ; 
 int FIELD_GET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_BBP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT_BBP_AGC_LNA_HIGH_GAIN ; 
 int /*<<< orphan*/  mt76_rmw_field (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_rr (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mt76x2_adjust_high_lna_gain(struct mt76x02_dev *dev, int reg, s8 offset)
{
	s8 gain;

	gain = FIELD_GET(MT_BBP_AGC_LNA_HIGH_GAIN,
			 mt76_rr(dev, MT_BBP(AGC, reg)));
	gain -= offset / 2;
	mt76_rmw_field(dev, MT_BBP(AGC, reg), MT_BBP_AGC_LNA_HIGH_GAIN, gain);
}