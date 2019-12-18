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
struct wmi_set_mac_address_cmd {int /*<<< orphan*/  mac; } ;
struct wil6210_vif {int /*<<< orphan*/  mid; } ;
struct wil6210_priv {int /*<<< orphan*/  main_ndev; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  WMI_SET_MAC_ADDRESS_CMDID ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,void*) ; 
 struct wil6210_vif* ndev_to_vif (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wil_dbg_wmi (struct wil6210_priv*,char*,void*) ; 
 int wmi_send (struct wil6210_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wmi_set_mac_address_cmd*,int) ; 

int wmi_set_mac_address(struct wil6210_priv *wil, void *addr)
{
	struct wil6210_vif *vif = ndev_to_vif(wil->main_ndev);
	struct wmi_set_mac_address_cmd cmd;

	ether_addr_copy(cmd.mac, addr);

	wil_dbg_wmi(wil, "Set MAC %pM\n", addr);

	return wmi_send(wil, WMI_SET_MAC_ADDRESS_CMDID, vif->mid,
			&cmd, sizeof(cmd));
}