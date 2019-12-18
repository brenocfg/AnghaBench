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
typedef  int u32 ;
struct mt76x02_patch_header {int /*<<< orphan*/  build_time; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mt76x02_dev {TYPE_1__ mt76; } ;
struct firmware {int size; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int BIT (int) ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MT7662_ROM_PATCH ; 
 scalar_t__ MT76XX_REV_E3 ; 
 int MT_MCU_CLOCK_CTL ; 
 int MT_MCU_COM_REG0 ; 
 int /*<<< orphan*/  MT_MCU_INT_LEVEL ; 
 int /*<<< orphan*/  MT_MCU_PCIE_REMAP_BASE4 ; 
 int /*<<< orphan*/  MT_MCU_ROM_PATCH_ADDR ; 
 int MT_MCU_ROM_PATCH_OFFSET ; 
 int /*<<< orphan*/  MT_MCU_SEMAPHORE_03 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  is_mt7612 (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76_poll (struct mt76x02_dev*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  mt76_poll_msec (struct mt76x02_dev*,int,int,int,int) ; 
 int mt76_rr (struct mt76x02_dev*,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr_copy (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ mt76xx_rev (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt76pci_load_rom_patch(struct mt76x02_dev *dev)
{
	const struct firmware *fw = NULL;
	struct mt76x02_patch_header *hdr;
	bool rom_protect = !is_mt7612(dev);
	int len, ret = 0;
	__le32 *cur;
	u32 patch_mask, patch_reg;

	if (rom_protect && !mt76_poll(dev, MT_MCU_SEMAPHORE_03, 1, 1, 600)) {
		dev_err(dev->mt76.dev,
			"Could not get hardware semaphore for ROM PATCH\n");
		return -ETIMEDOUT;
	}

	if (mt76xx_rev(dev) >= MT76XX_REV_E3) {
		patch_mask = BIT(0);
		patch_reg = MT_MCU_CLOCK_CTL;
	} else {
		patch_mask = BIT(1);
		patch_reg = MT_MCU_COM_REG0;
	}

	if (rom_protect && (mt76_rr(dev, patch_reg) & patch_mask)) {
		dev_info(dev->mt76.dev, "ROM patch already applied\n");
		goto out;
	}

	ret = request_firmware(&fw, MT7662_ROM_PATCH, dev->mt76.dev);
	if (ret)
		goto out;

	if (!fw || !fw->data || fw->size <= sizeof(*hdr)) {
		ret = -EIO;
		dev_err(dev->mt76.dev, "Failed to load firmware\n");
		goto out;
	}

	hdr = (struct mt76x02_patch_header *)fw->data;
	dev_info(dev->mt76.dev, "ROM patch build: %.15s\n", hdr->build_time);

	mt76_wr(dev, MT_MCU_PCIE_REMAP_BASE4, MT_MCU_ROM_PATCH_OFFSET);

	cur = (__le32 *)(fw->data + sizeof(*hdr));
	len = fw->size - sizeof(*hdr);
	mt76_wr_copy(dev, MT_MCU_ROM_PATCH_ADDR, cur, len);

	mt76_wr(dev, MT_MCU_PCIE_REMAP_BASE4, 0);

	/* Trigger ROM */
	mt76_wr(dev, MT_MCU_INT_LEVEL, 4);

	if (!mt76_poll_msec(dev, patch_reg, patch_mask, patch_mask, 2000)) {
		dev_err(dev->mt76.dev, "Failed to load ROM patch\n");
		ret = -ETIMEDOUT;
	}

out:
	/* release semaphore */
	if (rom_protect)
		mt76_wr(dev, MT_MCU_SEMAPHORE_03, 1);
	release_firmware(fw);
	return ret;
}