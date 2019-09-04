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
struct hci_dev {int dummy; } ;
struct TYPE_2__ {int gpio_gap; int psmode; } ;
struct btmrvl_private {TYPE_1__ btmrvl_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODULE_BRINGUP_REQ ; 
 int /*<<< orphan*/  btmrvl_check_device_tree (struct btmrvl_private*) ; 
 int /*<<< orphan*/  btmrvl_enable_ps (struct btmrvl_private*) ; 
 int /*<<< orphan*/  btmrvl_enable_sco_routing_to_host (struct btmrvl_private*) ; 
 int /*<<< orphan*/  btmrvl_pscan_window_reporting (struct btmrvl_private*,int) ; 
 int /*<<< orphan*/  btmrvl_send_hscfg_cmd (struct btmrvl_private*) ; 
 int btmrvl_send_module_cfg_cmd (struct btmrvl_private*,int /*<<< orphan*/ ) ; 
 struct btmrvl_private* hci_get_drvdata (struct hci_dev*) ; 

__attribute__((used)) static int btmrvl_setup(struct hci_dev *hdev)
{
	struct btmrvl_private *priv = hci_get_drvdata(hdev);
	int ret;

	ret = btmrvl_send_module_cfg_cmd(priv, MODULE_BRINGUP_REQ);
	if (ret)
		return ret;

	priv->btmrvl_dev.gpio_gap = 0xfffe;

	btmrvl_check_device_tree(priv);

	btmrvl_enable_sco_routing_to_host(priv);

	btmrvl_pscan_window_reporting(priv, 0x01);

	priv->btmrvl_dev.psmode = 1;
	btmrvl_enable_ps(priv);

	btmrvl_send_hscfg_cmd(priv);

	return 0;
}