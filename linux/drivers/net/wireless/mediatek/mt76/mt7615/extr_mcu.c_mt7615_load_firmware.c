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
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mt7615_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FIELD_PREP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FW_STATE_CR4_RDY ; 
 scalar_t__ FW_STATE_FW_DOWNLOAD ; 
 int /*<<< orphan*/  MT_TOP_MISC2 ; 
 int /*<<< orphan*/  MT_TOP_MISC2_FW_STATE ; 
 int /*<<< orphan*/  MT_TXQ_FWDL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int mt7615_load_patch (struct mt7615_dev*) ; 
 int mt7615_load_ram (struct mt7615_dev*) ; 
 scalar_t__ mt76_get_field (struct mt7615_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_poll_msec (struct mt7615_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_queue_tx_cleanup (struct mt7615_dev*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mt7615_load_firmware(struct mt7615_dev *dev)
{
	int ret;
	u32 val;

	val = mt76_get_field(dev, MT_TOP_MISC2, MT_TOP_MISC2_FW_STATE);

	if (val != FW_STATE_FW_DOWNLOAD) {
		dev_err(dev->mt76.dev, "Firmware is not ready for download\n");
		return -EIO;
	}

	ret = mt7615_load_patch(dev);
	if (ret)
		return ret;

	ret = mt7615_load_ram(dev);
	if (ret)
		return ret;

	if (!mt76_poll_msec(dev, MT_TOP_MISC2, MT_TOP_MISC2_FW_STATE,
			    FIELD_PREP(MT_TOP_MISC2_FW_STATE,
				       FW_STATE_CR4_RDY), 500)) {
		dev_err(dev->mt76.dev, "Timeout for initializing firmware\n");
		return -EIO;
	}

	mt76_queue_tx_cleanup(dev, MT_TXQ_FWDL, false);

	dev_dbg(dev->mt76.dev, "Firmware init done\n");

	return 0;
}