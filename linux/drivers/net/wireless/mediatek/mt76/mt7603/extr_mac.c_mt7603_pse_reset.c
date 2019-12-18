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
struct mt7603_dev {int* reset_cause; } ;

/* Variables and functions */
 int /*<<< orphan*/  MT_MCU_DEBUG_RESET ; 
 int /*<<< orphan*/  MT_MCU_DEBUG_RESET_PSE ; 
 int /*<<< orphan*/  MT_MCU_DEBUG_RESET_PSE_S ; 
 int /*<<< orphan*/  MT_MCU_DEBUG_RESET_QUEUES ; 
 size_t RESET_CAUSE_RESET_FAILED ; 
 int /*<<< orphan*/  mt76_clear (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_poll_msec (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_set (struct mt7603_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mt7603_pse_reset(struct mt7603_dev *dev)
{
	/* Clear previous reset result */
	if (!dev->reset_cause[RESET_CAUSE_RESET_FAILED])
		mt76_clear(dev, MT_MCU_DEBUG_RESET, MT_MCU_DEBUG_RESET_PSE_S);

	/* Reset PSE */
	mt76_set(dev, MT_MCU_DEBUG_RESET, MT_MCU_DEBUG_RESET_PSE);

	if (!mt76_poll_msec(dev, MT_MCU_DEBUG_RESET,
			    MT_MCU_DEBUG_RESET_PSE_S,
			    MT_MCU_DEBUG_RESET_PSE_S, 500)) {
		dev->reset_cause[RESET_CAUSE_RESET_FAILED]++;
		mt76_clear(dev, MT_MCU_DEBUG_RESET, MT_MCU_DEBUG_RESET_PSE);
	} else {
		dev->reset_cause[RESET_CAUSE_RESET_FAILED] = 0;
		mt76_clear(dev, MT_MCU_DEBUG_RESET, MT_MCU_DEBUG_RESET_QUEUES);
	}

	if (dev->reset_cause[RESET_CAUSE_RESET_FAILED] >= 3)
		dev->reset_cause[RESET_CAUSE_RESET_FAILED] = 0;
}