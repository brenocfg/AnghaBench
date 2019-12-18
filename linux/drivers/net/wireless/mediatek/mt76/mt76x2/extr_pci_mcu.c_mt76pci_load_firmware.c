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
struct mt76x02_fw_header {int /*<<< orphan*/  dlm_len; int /*<<< orphan*/  ilm_len; int /*<<< orphan*/  build_time; int /*<<< orphan*/  build_ver; int /*<<< orphan*/  fw_ver; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mt76x02_dev {TYPE_1__ mt76; } ;
struct firmware {int size; scalar_t__ data; } ;
typedef  int /*<<< orphan*/  __le32 ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int) ; 
 int ENOENT ; 
 int ETIMEDOUT ; 
 int FIELD_GET (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MT7662_FIRMWARE ; 
 scalar_t__ MT76XX_REV_E3 ; 
 int /*<<< orphan*/  MT_EE_NIC_CONF_2 ; 
 int /*<<< orphan*/  MT_EE_NIC_CONF_2_XTAL_OPTION ; 
 int /*<<< orphan*/  MT_MCU_COM_REG0 ; 
 int MT_MCU_DLM_ADDR ; 
 int MT_MCU_DLM_ADDR_E3 ; 
 int MT_MCU_DLM_OFFSET ; 
 int MT_MCU_ILM_ADDR ; 
 int MT_MCU_ILM_OFFSET ; 
 int /*<<< orphan*/  MT_MCU_INT_LEVEL ; 
 int /*<<< orphan*/  MT_MCU_PCIE_REMAP_BASE4 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,...) ; 
 int le16_to_cpu (int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_poll_msec (struct mt76x02_dev*,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  mt76_set (struct mt76x02_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_wr (struct mt76x02_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mt76_wr_copy (struct mt76x02_dev*,int,int /*<<< orphan*/ *,int) ; 
 int mt76x02_eeprom_get (struct mt76x02_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76x02_set_ethtool_fwver (struct mt76x02_dev*,struct mt76x02_fw_header const*) ; 
 scalar_t__ mt76xx_rev (struct mt76x02_dev*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mt76pci_load_firmware(struct mt76x02_dev *dev)
{
	const struct firmware *fw;
	const struct mt76x02_fw_header *hdr;
	int len, ret;
	__le32 *cur;
	u32 offset, val;

	ret = request_firmware(&fw, MT7662_FIRMWARE, dev->mt76.dev);
	if (ret)
		return ret;

	if (!fw || !fw->data || fw->size < sizeof(*hdr))
		goto error;

	hdr = (const struct mt76x02_fw_header *)fw->data;

	len = sizeof(*hdr);
	len += le32_to_cpu(hdr->ilm_len);
	len += le32_to_cpu(hdr->dlm_len);

	if (fw->size != len)
		goto error;

	val = le16_to_cpu(hdr->fw_ver);
	dev_info(dev->mt76.dev, "Firmware Version: %d.%d.%02d\n",
		 (val >> 12) & 0xf, (val >> 8) & 0xf, val & 0xf);

	val = le16_to_cpu(hdr->build_ver);
	dev_info(dev->mt76.dev, "Build: %x\n", val);
	dev_info(dev->mt76.dev, "Build Time: %.16s\n", hdr->build_time);

	cur = (__le32 *)(fw->data + sizeof(*hdr));
	len = le32_to_cpu(hdr->ilm_len);

	mt76_wr(dev, MT_MCU_PCIE_REMAP_BASE4, MT_MCU_ILM_OFFSET);
	mt76_wr_copy(dev, MT_MCU_ILM_ADDR, cur, len);

	cur += len / sizeof(*cur);
	len = le32_to_cpu(hdr->dlm_len);

	if (mt76xx_rev(dev) >= MT76XX_REV_E3)
		offset = MT_MCU_DLM_ADDR_E3;
	else
		offset = MT_MCU_DLM_ADDR;

	mt76_wr(dev, MT_MCU_PCIE_REMAP_BASE4, MT_MCU_DLM_OFFSET);
	mt76_wr_copy(dev, offset, cur, len);

	mt76_wr(dev, MT_MCU_PCIE_REMAP_BASE4, 0);

	val = mt76x02_eeprom_get(dev, MT_EE_NIC_CONF_2);
	if (FIELD_GET(MT_EE_NIC_CONF_2_XTAL_OPTION, val) == 1)
		mt76_set(dev, MT_MCU_COM_REG0, BIT(30));

	/* trigger firmware */
	mt76_wr(dev, MT_MCU_INT_LEVEL, 2);
	if (!mt76_poll_msec(dev, MT_MCU_COM_REG0, 1, 1, 200)) {
		dev_err(dev->mt76.dev, "Firmware failed to start\n");
		release_firmware(fw);
		return -ETIMEDOUT;
	}

	mt76x02_set_ethtool_fwver(dev, hdr);
	dev_info(dev->mt76.dev, "Firmware running!\n");

	release_firmware(fw);

	return ret;

error:
	dev_err(dev->mt76.dev, "Invalid firmware\n");
	release_firmware(fw);
	return -ENOENT;
}