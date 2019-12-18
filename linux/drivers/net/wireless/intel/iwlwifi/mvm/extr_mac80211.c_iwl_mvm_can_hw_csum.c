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
typedef  scalar_t__ u8 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ protocol; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_INET ; 
 scalar_t__ IPPROTO_TCP ; 
 scalar_t__ IPPROTO_UDP ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 

__attribute__((used)) static bool iwl_mvm_can_hw_csum(struct sk_buff *skb)
{
	u8 protocol = ip_hdr(skb)->protocol;

	if (!IS_ENABLED(CONFIG_INET))
		return false;

	return protocol == IPPROTO_TCP || protocol == IPPROTO_UDP;
}