#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct rtl8xxxu_priv {scalar_t__ rtl_chip; TYPE_2__* fops; TYPE_1__* udev; } ;
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* reset_8051 ) (struct rtl8xxxu_priv*) ;} ;
struct TYPE_3__ {struct device dev; } ;

/* Variables and functions */
 int EAGAIN ; 
 int MCU_FW_DL_CSUM_REPORT ; 
 int MCU_FW_DL_READY ; 
 int MCU_WINT_INIT_READY ; 
 int /*<<< orphan*/  REG_HMTFR ; 
 int /*<<< orphan*/  REG_MCU_FW_DL ; 
 scalar_t__ RTL8723B ; 
 int RTL8XXXU_FIRMWARE_POLL_MAX ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*) ; 
 int rtl8xxxu_read32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtl8xxxu_write32 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl8xxxu_write8 (struct rtl8xxxu_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct rtl8xxxu_priv*) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int rtl8xxxu_start_firmware(struct rtl8xxxu_priv *priv)
{
	struct device *dev = &priv->udev->dev;
	int ret = 0, i;
	u32 val32;

	/* Poll checksum report */
	for (i = 0; i < RTL8XXXU_FIRMWARE_POLL_MAX; i++) {
		val32 = rtl8xxxu_read32(priv, REG_MCU_FW_DL);
		if (val32 & MCU_FW_DL_CSUM_REPORT)
			break;
	}

	if (i == RTL8XXXU_FIRMWARE_POLL_MAX) {
		dev_warn(dev, "Firmware checksum poll timed out\n");
		ret = -EAGAIN;
		goto exit;
	}

	val32 = rtl8xxxu_read32(priv, REG_MCU_FW_DL);
	val32 |= MCU_FW_DL_READY;
	val32 &= ~MCU_WINT_INIT_READY;
	rtl8xxxu_write32(priv, REG_MCU_FW_DL, val32);

	/*
	 * Reset the 8051 in order for the firmware to start running,
	 * otherwise it won't come up on the 8192eu
	 */
	priv->fops->reset_8051(priv);

	/* Wait for firmware to become ready */
	for (i = 0; i < RTL8XXXU_FIRMWARE_POLL_MAX; i++) {
		val32 = rtl8xxxu_read32(priv, REG_MCU_FW_DL);
		if (val32 & MCU_WINT_INIT_READY)
			break;

		udelay(100);
	}

	if (i == RTL8XXXU_FIRMWARE_POLL_MAX) {
		dev_warn(dev, "Firmware failed to start\n");
		ret = -EAGAIN;
		goto exit;
	}

	/*
	 * Init H2C command
	 */
	if (priv->rtl_chip == RTL8723B)
		rtl8xxxu_write8(priv, REG_HMTFR, 0x0f);
exit:
	return ret;
}