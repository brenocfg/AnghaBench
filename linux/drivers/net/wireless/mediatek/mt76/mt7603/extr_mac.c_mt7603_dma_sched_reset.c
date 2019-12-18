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
struct mt7603_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_SCH_4 ; 
 int /*<<< orphan*/  MT_SCH_4_RESET ; 
 int /*<<< orphan*/  is_mt7628 (struct mt7603_dev*) ; 
 int /*<<< orphan*/  mt76_clear (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_set (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt7603_dma_sched_reset(struct mt7603_dev *dev)
{
	if (!is_mt7628(dev))
		return;

	mt76_set(dev, MT_SCH_4, MT_SCH_4_RESET);
	mt76_clear(dev, MT_SCH_4, MT_SCH_4_RESET);
}