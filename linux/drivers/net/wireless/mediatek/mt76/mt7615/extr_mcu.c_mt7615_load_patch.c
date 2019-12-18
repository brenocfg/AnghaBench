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
struct mt7615_patch_hdr {int /*<<< orphan*/  build_date; int /*<<< orphan*/  hw_sw_ver; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mt7615_dev {TYPE_1__ mt76; } ;
struct firmware {int size; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DL_MODE_NEED_RSP ; 
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  MCU_PATCH_ADDRESS ; 
 int /*<<< orphan*/  MT7615_ROM_PATCH ; 
#define  PATCH_IS_DL 130 
#define  PATCH_NOT_DL_SEM_SUCCESS 129 
#define  PATCH_REL_SEM_SUCCESS 128 
 int /*<<< orphan*/  be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mt7615_mcu_init_download (struct mt7615_dev*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int mt7615_mcu_patch_sem_ctrl (struct mt7615_dev*,int) ; 
 int mt7615_mcu_send_firmware (struct mt7615_dev*,scalar_t__,int) ; 
 int mt7615_mcu_start_patch (struct mt7615_dev*) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mt7615_load_patch(struct mt7615_dev *dev)
{
	const struct mt7615_patch_hdr *hdr;
	const struct firmware *fw = NULL;
	int len, ret, sem;

	sem = mt7615_mcu_patch_sem_ctrl(dev, 1);
	switch (sem) {
	case PATCH_IS_DL:
		return 0;
	case PATCH_NOT_DL_SEM_SUCCESS:
		break;
	default:
		dev_err(dev->mt76.dev, "Failed to get patch semaphore\n");
		return -EAGAIN;
	}

	ret = request_firmware(&fw, MT7615_ROM_PATCH, dev->mt76.dev);
	if (ret)
		goto out;

	if (!fw || !fw->data || fw->size < sizeof(*hdr)) {
		dev_err(dev->mt76.dev, "Invalid firmware\n");
		ret = -EINVAL;
		goto out;
	}

	hdr = (const struct mt7615_patch_hdr *)(fw->data);

	dev_info(dev->mt76.dev, "HW/SW Version: 0x%x, Build Time: %.16s\n",
		 be32_to_cpu(hdr->hw_sw_ver), hdr->build_date);

	len = fw->size - sizeof(*hdr);

	ret = mt7615_mcu_init_download(dev, MCU_PATCH_ADDRESS, len,
				       DL_MODE_NEED_RSP);
	if (ret) {
		dev_err(dev->mt76.dev, "Download request failed\n");
		goto out;
	}

	ret = mt7615_mcu_send_firmware(dev, fw->data + sizeof(*hdr), len);
	if (ret) {
		dev_err(dev->mt76.dev, "Failed to send firmware to device\n");
		goto out;
	}

	ret = mt7615_mcu_start_patch(dev);
	if (ret)
		dev_err(dev->mt76.dev, "Failed to start patch\n");

out:
	release_firmware(fw);

	sem = mt7615_mcu_patch_sem_ctrl(dev, 0);
	switch (sem) {
	case PATCH_REL_SEM_SUCCESS:
		break;
	default:
		ret = -EAGAIN;
		dev_err(dev->mt76.dev, "Failed to release patch semaphore\n");
		break;
	}

	return ret;
}