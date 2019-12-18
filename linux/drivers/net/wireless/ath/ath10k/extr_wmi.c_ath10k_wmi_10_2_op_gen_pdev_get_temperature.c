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
struct sk_buff {int dummy; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_WMI ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct sk_buff* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*) ; 
 struct sk_buff* ath10k_wmi_alloc_skb (struct ath10k*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sk_buff *
ath10k_wmi_10_2_op_gen_pdev_get_temperature(struct ath10k *ar)
{
	struct sk_buff *skb;

	skb = ath10k_wmi_alloc_skb(ar, 0);
	if (!skb)
		return ERR_PTR(-ENOMEM);

	ath10k_dbg(ar, ATH10K_DBG_WMI, "wmi pdev get temperature\n");
	return skb;
}