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
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*,int) ; 
 int ath10k_wmi_rx (struct ath10k*,struct sk_buff*) ; 

__attribute__((used)) static void ath10k_wmi_process_rx(struct ath10k *ar, struct sk_buff *skb)
{
	int ret;

	ret = ath10k_wmi_rx(ar, skb);
	if (ret)
		ath10k_warn(ar, "failed to process wmi rx: %d\n", ret);
}