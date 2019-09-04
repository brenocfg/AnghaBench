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
struct TYPE_2__ {int tx_flags; } ;

/* Variables and functions */
 int SKBTX_HW_TSTAMP ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static inline bool cxgb4_xmit_with_hwtstamp(struct sk_buff *skb)
{
	return skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP;
}