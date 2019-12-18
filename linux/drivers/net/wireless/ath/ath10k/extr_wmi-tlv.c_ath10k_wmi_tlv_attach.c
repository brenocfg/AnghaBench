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
struct TYPE_2__ {int /*<<< orphan*/ * peer_flags; int /*<<< orphan*/ * ops; int /*<<< orphan*/ * pdev_param; int /*<<< orphan*/ * vdev_param; int /*<<< orphan*/ * cmd; } ;
struct ath10k {TYPE_1__ wmi; } ;

/* Variables and functions */
 int /*<<< orphan*/  wmi_tlv_cmd_map ; 
 int /*<<< orphan*/  wmi_tlv_ops ; 
 int /*<<< orphan*/  wmi_tlv_pdev_param_map ; 
 int /*<<< orphan*/  wmi_tlv_peer_flags_map ; 
 int /*<<< orphan*/  wmi_tlv_vdev_param_map ; 

void ath10k_wmi_tlv_attach(struct ath10k *ar)
{
	ar->wmi.cmd = &wmi_tlv_cmd_map;
	ar->wmi.vdev_param = &wmi_tlv_vdev_param_map;
	ar->wmi.pdev_param = &wmi_tlv_pdev_param_map;
	ar->wmi.ops = &wmi_tlv_ops;
	ar->wmi.peer_flags = &wmi_tlv_peer_flags_map;
}