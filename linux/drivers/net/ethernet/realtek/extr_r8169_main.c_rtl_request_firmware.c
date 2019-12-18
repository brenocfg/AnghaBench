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
struct rtl_fw {int /*<<< orphan*/  dev; scalar_t__ fw_name; int /*<<< orphan*/  mac_mcu_read; int /*<<< orphan*/  mac_mcu_write; int /*<<< orphan*/  phy_read; int /*<<< orphan*/  phy_write; } ;
struct rtl8169_private {struct rtl_fw* rtl_fw; scalar_t__ fw_name; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  kfree (struct rtl_fw*) ; 
 struct rtl_fw* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_mcu_read ; 
 int /*<<< orphan*/  mac_mcu_write ; 
 int /*<<< orphan*/  netif_warn (struct rtl8169_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ rtl_fw_request_firmware (struct rtl_fw*) ; 
 int /*<<< orphan*/  rtl_readphy ; 
 int /*<<< orphan*/  rtl_writephy ; 
 int /*<<< orphan*/  tp_to_dev (struct rtl8169_private*) ; 

__attribute__((used)) static void rtl_request_firmware(struct rtl8169_private *tp)
{
	struct rtl_fw *rtl_fw;

	/* firmware loaded already or no firmware available */
	if (tp->rtl_fw || !tp->fw_name)
		return;

	rtl_fw = kzalloc(sizeof(*rtl_fw), GFP_KERNEL);
	if (!rtl_fw) {
		netif_warn(tp, ifup, tp->dev, "Unable to load firmware, out of memory\n");
		return;
	}

	rtl_fw->phy_write = rtl_writephy;
	rtl_fw->phy_read = rtl_readphy;
	rtl_fw->mac_mcu_write = mac_mcu_write;
	rtl_fw->mac_mcu_read = mac_mcu_read;
	rtl_fw->fw_name = tp->fw_name;
	rtl_fw->dev = tp_to_dev(tp);

	if (rtl_fw_request_firmware(rtl_fw))
		kfree(rtl_fw);
	else
		tp->rtl_fw = rtl_fw;
}