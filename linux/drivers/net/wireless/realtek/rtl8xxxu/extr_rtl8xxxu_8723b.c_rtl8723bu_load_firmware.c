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
struct rtl8xxxu_priv {scalar_t__ enable_bluetooth; } ;

/* Variables and functions */
 int rtl8xxxu_load_firmware (struct rtl8xxxu_priv*,char*) ; 

__attribute__((used)) static int rtl8723bu_load_firmware(struct rtl8xxxu_priv *priv)
{
	char *fw_name;
	int ret;

	if (priv->enable_bluetooth)
		fw_name = "rtlwifi/rtl8723bu_bt.bin";
	else
		fw_name = "rtlwifi/rtl8723bu_nic.bin";

	ret = rtl8xxxu_load_firmware(priv, fw_name);
	return ret;
}