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
struct sk_buff {int dummy; } ;
struct rtw_pci_tx_data {int dummy; } ;
struct TYPE_2__ {scalar_t__ status_driver_data; } ;
struct ieee80211_tx_info {TYPE_1__ status; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 

__attribute__((used)) static inline struct
rtw_pci_tx_data *rtw_pci_get_tx_data(struct sk_buff *skb)
{
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);

	BUILD_BUG_ON(sizeof(struct rtw_pci_tx_data) >
		     sizeof(info->status.status_driver_data));

	return (struct rtw_pci_tx_data *)info->status.status_driver_data;
}