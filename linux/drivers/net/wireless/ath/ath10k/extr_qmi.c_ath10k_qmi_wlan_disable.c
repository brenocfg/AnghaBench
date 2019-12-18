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
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  QMI_WLFW_OFF_V01 ; 
 int ath10k_qmi_mode_send_sync_msg (struct ath10k*,int /*<<< orphan*/ ) ; 

int ath10k_qmi_wlan_disable(struct ath10k *ar)
{
	return ath10k_qmi_mode_send_sync_msg(ar, QMI_WLFW_OFF_V01);
}