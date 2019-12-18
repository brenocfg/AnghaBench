#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct mt7603_fw_trailer {char* fw_ver; char* build_date; int /*<<< orphan*/  dl_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; TYPE_2__* hw; } ;
struct mt7603_dev {int mcu_running; TYPE_3__ mt76; } ;
struct firmware {int data; int size; } ;
struct TYPE_5__ {TYPE_1__* wiphy; } ;
struct TYPE_4__ {int /*<<< orphan*/  fw_version; } ;

/* Variables and functions */
 int BIT (int) ; 
 int EINVAL ; 
 int EIO ; 
 int FIELD_PREP (int,int) ; 
 int /*<<< orphan*/  MCU_FIRMWARE_ADDRESS ; 
 char* MT7603_FIRMWARE_E1 ; 
 char* MT7603_FIRMWARE_E2 ; 
 scalar_t__ MT7603_REV_E2 ; 
 char* MT7628_FIRMWARE_E1 ; 
 char* MT7628_FIRMWARE_E2 ; 
 scalar_t__ MT7628_REV_E1 ; 
 int /*<<< orphan*/  MT_SCH_4 ; 
 int MT_SCH_4_BYPASS ; 
 int MT_SCH_4_FORCE_QID ; 
 int /*<<< orphan*/  MT_TOP_MISC2 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ is_mt7628 (struct mt7603_dev*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int mt7603_mcu_init_download (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 
 int mt7603_mcu_send_firmware (struct mt7603_dev*,int,int) ; 
 int mt7603_mcu_start_firmware (struct mt7603_dev*,int /*<<< orphan*/ ) ; 
 int mt7603_reg_map (struct mt7603_dev*,int) ; 
 int /*<<< orphan*/  mt76_clear (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_poll_msec (struct mt7603_dev*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  mt76_rmw (struct mt7603_dev*,int /*<<< orphan*/ ,int,int) ; 
 int mt76_rr (struct mt7603_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_set (struct mt7603_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt7603_dev*,int,int) ; 
 scalar_t__ mt76xx_rev (struct mt7603_dev*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int mt7603_load_firmware(struct mt7603_dev *dev)
{
	const struct firmware *fw;
	const struct mt7603_fw_trailer *hdr;
	const char *firmware;
	int dl_len;
	u32 addr, val;
	int ret;

	if (is_mt7628(dev)) {
		if (mt76xx_rev(dev) == MT7628_REV_E1)
			firmware = MT7628_FIRMWARE_E1;
		else
			firmware = MT7628_FIRMWARE_E2;
	} else {
		if (mt76xx_rev(dev) < MT7603_REV_E2)
			firmware = MT7603_FIRMWARE_E1;
		else
			firmware = MT7603_FIRMWARE_E2;
	}

	ret = request_firmware(&fw, firmware, dev->mt76.dev);
	if (ret)
		return ret;

	if (!fw || !fw->data || fw->size < sizeof(*hdr)) {
		dev_err(dev->mt76.dev, "Invalid firmware\n");
		ret = -EINVAL;
		goto out;
	}

	hdr = (const struct mt7603_fw_trailer *)(fw->data + fw->size -
						 sizeof(*hdr));

	dev_info(dev->mt76.dev, "Firmware Version: %.10s\n", hdr->fw_ver);
	dev_info(dev->mt76.dev, "Build Time: %.15s\n", hdr->build_date);

	addr = mt7603_reg_map(dev, 0x50012498);
	mt76_wr(dev, addr, 0x5);
	mt76_wr(dev, addr, 0x5);
	udelay(1);

	/* switch to bypass mode */
	mt76_rmw(dev, MT_SCH_4, MT_SCH_4_FORCE_QID,
		 MT_SCH_4_BYPASS | FIELD_PREP(MT_SCH_4_FORCE_QID, 5));

	val = mt76_rr(dev, MT_TOP_MISC2);
	if (val & BIT(1)) {
		dev_info(dev->mt76.dev, "Firmware already running...\n");
		goto running;
	}

	if (!mt76_poll_msec(dev, MT_TOP_MISC2, BIT(0) | BIT(1), BIT(0), 500)) {
		dev_err(dev->mt76.dev, "Timeout waiting for ROM code to become ready\n");
		ret = -EIO;
		goto out;
	}

	dl_len = le32_to_cpu(hdr->dl_len) + 4;
	ret = mt7603_mcu_init_download(dev, MCU_FIRMWARE_ADDRESS, dl_len);
	if (ret) {
		dev_err(dev->mt76.dev, "Download request failed\n");
		goto out;
	}

	ret = mt7603_mcu_send_firmware(dev, fw->data, dl_len);
	if (ret) {
		dev_err(dev->mt76.dev, "Failed to send firmware to device\n");
		goto out;
	}

	ret = mt7603_mcu_start_firmware(dev, MCU_FIRMWARE_ADDRESS);
	if (ret) {
		dev_err(dev->mt76.dev, "Failed to start firmware\n");
		goto out;
	}

	if (!mt76_poll_msec(dev, MT_TOP_MISC2, BIT(1), BIT(1), 500)) {
		dev_err(dev->mt76.dev, "Timeout waiting for firmware to initialize\n");
		ret = -EIO;
		goto out;
	}

running:
	mt76_clear(dev, MT_SCH_4, MT_SCH_4_FORCE_QID | MT_SCH_4_BYPASS);

	mt76_set(dev, MT_SCH_4, BIT(8));
	mt76_clear(dev, MT_SCH_4, BIT(8));

	dev->mcu_running = true;
	snprintf(dev->mt76.hw->wiphy->fw_version,
		 sizeof(dev->mt76.hw->wiphy->fw_version),
		 "%.10s-%.15s", hdr->fw_ver, hdr->build_date);
	dev_info(dev->mt76.dev, "firmware init done\n");

out:
	release_firmware(fw);

	return ret;
}