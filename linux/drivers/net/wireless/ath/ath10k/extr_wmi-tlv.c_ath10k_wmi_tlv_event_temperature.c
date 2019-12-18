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
struct wmi_tlv_pdev_temperature_event {int /*<<< orphan*/  temperature; } ;
struct sk_buff {int len; scalar_t__ data; } ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 int EPROTO ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  __le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath10k_thermal_event_temperature (struct ath10k*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ath10k_wmi_tlv_event_temperature(struct ath10k *ar,
					    struct sk_buff *skb)
{
	const struct wmi_tlv_pdev_temperature_event *ev;

	ev = (struct wmi_tlv_pdev_temperature_event *)skb->data;
	if (WARN_ON(skb->len < sizeof(*ev)))
		return -EPROTO;

	ath10k_thermal_event_temperature(ar, __le32_to_cpu(ev->temperature));
	return 0;
}