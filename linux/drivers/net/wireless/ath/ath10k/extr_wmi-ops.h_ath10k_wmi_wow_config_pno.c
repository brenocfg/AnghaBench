#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct wmi_pno_scan_req {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {TYPE_2__* cmd; TYPE_1__* ops; } ;
struct ath10k {TYPE_3__ wmi; } ;
struct TYPE_5__ {int /*<<< orphan*/  network_list_offload_config_cmdid; } ;
struct TYPE_4__ {struct sk_buff* (* gen_wow_config_pno ) (struct ath10k*,int /*<<< orphan*/ ,struct wmi_pno_scan_req*) ;} ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int PTR_ERR (struct sk_buff*) ; 
 int ath10k_wmi_cmd_send (struct ath10k*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct sk_buff* stub1 (struct ath10k*,int /*<<< orphan*/ ,struct wmi_pno_scan_req*) ; 

__attribute__((used)) static inline int
ath10k_wmi_wow_config_pno(struct ath10k *ar, u32 vdev_id,
			  struct wmi_pno_scan_req  *pno_scan)
{
	struct sk_buff *skb;
	u32 cmd_id;

	if (!ar->wmi.ops->gen_wow_config_pno)
		return -EOPNOTSUPP;

	skb = ar->wmi.ops->gen_wow_config_pno(ar, vdev_id, pno_scan);
	if (IS_ERR(skb))
		return PTR_ERR(skb);

	cmd_id = ar->wmi.cmd->network_list_offload_config_cmdid;
	return ath10k_wmi_cmd_send(ar, skb, cmd_id);
}