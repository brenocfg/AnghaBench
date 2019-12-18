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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mt7615_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  MT_CFG_LPCR_HOST ; 
 int /*<<< orphan*/  MT_CFG_LPCR_HOST_DRV_OWN ; 
 int /*<<< orphan*/  MT_CFG_LPCR_HOST_FW_OWN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mt76_poll_msec (struct mt7615_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7615_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7615_driver_own(struct mt7615_dev *dev)
{
	mt76_wr(dev, MT_CFG_LPCR_HOST, MT_CFG_LPCR_HOST_DRV_OWN);
	if (!mt76_poll_msec(dev, MT_CFG_LPCR_HOST,
			    MT_CFG_LPCR_HOST_FW_OWN, 0, 500)) {
		dev_err(dev->mt76.dev, "Timeout for driver own\n");
		return -EIO;
	}

	return 0;
}