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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct mt76x02_fw_header {int /*<<< orphan*/  ilm_len; int /*<<< orphan*/  dlm_len; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;
struct mt76x02_dev {TYPE_1__ mt76; } ;

/* Variables and functions */
 int ENOMEM ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MCU_FW_URB_MAX_PAYLOAD ; 
 int /*<<< orphan*/  MT_MCU_COM_REG0 ; 
 int MT_MCU_DLM_OFFSET ; 
 int MT_MCU_IVB_SIZE ; 
 int /*<<< orphan*/  MT_VEND_DEV_MODE ; 
 int USB_DIR_OUT ; 
 int USB_TYPE_VENDOR ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmemdup (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mt76_poll_msec (struct mt76x02_dev*,int /*<<< orphan*/ ,int,int,int) ; 
 int mt76u_vendor_request (TYPE_1__*,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,void*,int) ; 
 int mt76x02u_mcu_fw_send_data (struct mt76x02_dev*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
mt76x0u_upload_firmware(struct mt76x02_dev *dev,
			const struct mt76x02_fw_header *hdr)
{
	u8 *fw_payload = (u8 *)(hdr + 1);
	u32 ilm_len, dlm_len;
	void *ivb;
	int err;

	ivb = kmemdup(fw_payload, MT_MCU_IVB_SIZE, GFP_KERNEL);
	if (!ivb)
		return -ENOMEM;

	ilm_len = le32_to_cpu(hdr->ilm_len) - MT_MCU_IVB_SIZE;
	dev_dbg(dev->mt76.dev, "loading FW - ILM %u + IVB %u\n",
		ilm_len, MT_MCU_IVB_SIZE);
	err = mt76x02u_mcu_fw_send_data(dev, fw_payload + MT_MCU_IVB_SIZE,
					ilm_len, MCU_FW_URB_MAX_PAYLOAD,
					MT_MCU_IVB_SIZE);
	if (err)
		goto out;

	dlm_len = le32_to_cpu(hdr->dlm_len);
	dev_dbg(dev->mt76.dev, "loading FW - DLM %u\n", dlm_len);
	err = mt76x02u_mcu_fw_send_data(dev,
					fw_payload + le32_to_cpu(hdr->ilm_len),
					dlm_len, MCU_FW_URB_MAX_PAYLOAD,
					MT_MCU_DLM_OFFSET);
	if (err)
		goto out;

	err = mt76u_vendor_request(&dev->mt76, MT_VEND_DEV_MODE,
				   USB_DIR_OUT | USB_TYPE_VENDOR,
				   0x12, 0, ivb, MT_MCU_IVB_SIZE);
	if (err < 0)
		goto out;

	if (!mt76_poll_msec(dev, MT_MCU_COM_REG0, 1, 1, 1000)) {
		dev_err(dev->mt76.dev, "Firmware failed to start\n");
		err = -ETIMEDOUT;
		goto out;
	}

	dev_dbg(dev->mt76.dev, "Firmware running!\n");

out:
	kfree(ivb);

	return err;
}