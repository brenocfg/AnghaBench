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

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  CFG ; 
 int EIO ; 
 int ETIMEDOUT ; 
 int FIELD_PREP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MCU_ROM_PATCH_MAX_PAYLOAD ; 
 int /*<<< orphan*/  MT7662_ROM_PATCH ; 
 int /*<<< orphan*/  MT76U_MCU_ROM_PATCH_OFFSET ; 
 scalar_t__ MT76XX_REV_E3 ; 
 int MT_FCE_PDMA_GLOBAL_CONF ; 
 int MT_FCE_PSE_CTRL ; 
 int MT_FCE_SKIP_FS ; 
 int MT_MCU_CLOCK_CTL ; 
 int MT_MCU_COM_REG0 ; 
 int MT_MCU_SEMAPHORE_03 ; 
 int MT_TX_CPU_FROM_FCE_BASE_PTR ; 
 int MT_TX_CPU_FROM_FCE_MAX_COUNT ; 
 int /*<<< orphan*/  MT_USB_DMA_CFG_RX_BULK_AGG_TOUT ; 
 int MT_USB_DMA_CFG_RX_BULK_EN ; 
 int MT_USB_DMA_CFG_TX_BULK_EN ; 
 int /*<<< orphan*/  MT_USB_U3DMA_CFG ; 
 int MT_VEND_ADDR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  is_mt7612 (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  mt76_poll_msec (struct mt76x02_dev*,int,int,int,int) ; 
 int mt76_rr (struct mt76x02_dev*,int) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int,int) ; 
 int /*<<< orphan*/  mt76x02u_mcu_fw_reset (struct mt76x02_dev*) ; 
 int mt76x02u_mcu_fw_send_data (struct mt76x02_dev*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x2u_mcu_enable_patch (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  mt76x2u_mcu_reset_wmt (struct mt76x02_dev*) ; 
 scalar_t__ mt76xx_rev (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int mt76x2u_mcu_load_rom_patch(struct mt76x02_dev *dev)
{
	bool rom_protect = !is_mt7612(dev);
	struct mt76x02_patch_header *hdr;
	u32 val, patch_mask, patch_reg;
	const struct firmware *fw;
	int err;

	if (rom_protect &&
	    !mt76_poll_msec(dev, MT_MCU_SEMAPHORE_03, 1, 1, 600)) {
		dev_err(dev->mt76.dev,
			"could not get hardware semaphore for ROM PATCH\n");
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
		return 0;
	}

	err = request_firmware(&fw, MT7662_ROM_PATCH, dev->mt76.dev);
	if (err < 0)
		return err;

	if (!fw || !fw->data || fw->size <= sizeof(*hdr)) {
		dev_err(dev->mt76.dev, "failed to load firmware\n");
		err = -EIO;
		goto out;
	}

	hdr = (struct mt76x02_patch_header *)fw->data;
	dev_info(dev->mt76.dev, "ROM patch build: %.15s\n", hdr->build_time);

	/* enable USB_DMA_CFG */
	val = MT_USB_DMA_CFG_RX_BULK_EN |
	      MT_USB_DMA_CFG_TX_BULK_EN |
	      FIELD_PREP(MT_USB_DMA_CFG_RX_BULK_AGG_TOUT, 0x20);
	mt76_wr(dev, MT_VEND_ADDR(CFG, MT_USB_U3DMA_CFG), val);

	/* vendor reset */
	mt76x02u_mcu_fw_reset(dev);
	usleep_range(5000, 10000);

	/* enable FCE to send in-band cmd */
	mt76_wr(dev, MT_FCE_PSE_CTRL, 0x1);
	/* FCE tx_fs_base_ptr */
	mt76_wr(dev, MT_TX_CPU_FROM_FCE_BASE_PTR, 0x400230);
	/* FCE tx_fs_max_cnt */
	mt76_wr(dev, MT_TX_CPU_FROM_FCE_MAX_COUNT, 0x1);
	/* FCE pdma enable */
	mt76_wr(dev, MT_FCE_PDMA_GLOBAL_CONF, 0x44);
	/* FCE skip_fs_en */
	mt76_wr(dev, MT_FCE_SKIP_FS, 0x3);

	err = mt76x02u_mcu_fw_send_data(dev, fw->data + sizeof(*hdr),
					fw->size - sizeof(*hdr),
					MCU_ROM_PATCH_MAX_PAYLOAD,
					MT76U_MCU_ROM_PATCH_OFFSET);
	if (err < 0) {
		err = -EIO;
		goto out;
	}

	mt76x2u_mcu_enable_patch(dev);
	mt76x2u_mcu_reset_wmt(dev);
	mdelay(20);

	if (!mt76_poll_msec(dev, patch_reg, patch_mask, patch_mask, 100)) {
		dev_err(dev->mt76.dev, "failed to load ROM patch\n");
		err = -ETIMEDOUT;
	}

out:
	if (rom_protect)
		mt76_wr(dev, MT_MCU_SEMAPHORE_03, 1);
	release_firmware(fw);
	return err;
}