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
typedef  int /*<<< orphan*/  u32 ;
struct wmi_pno_scan_req {scalar_t__ enable; } ;
struct sk_buff {int dummy; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 struct sk_buff* ath10k_wmi_tlv_op_gen_config_pno_start (struct ath10k*,int /*<<< orphan*/ ,struct wmi_pno_scan_req*) ; 
 struct sk_buff* ath10k_wmi_tlv_op_gen_config_pno_stop (struct ath10k*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_tlv_op_gen_config_pno(struct ath10k *ar, u32 vdev_id,
				 struct wmi_pno_scan_req *pno_scan)
{
	if (pno_scan->enable)
		return ath10k_wmi_tlv_op_gen_config_pno_start(ar, vdev_id, pno_scan);
	else
		return ath10k_wmi_tlv_op_gen_config_pno_stop(ar, vdev_id);
}