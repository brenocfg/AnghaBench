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

/* Variables and functions */
 int I40E_MAX_BUFFER_TXD ; 
 int __i40e_chk_linearize (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 

__attribute__((used)) static inline bool i40e_chk_linearize(struct sk_buff *skb, int count)
{
	/* Both TSO and single send will work if count is less than 8 */
	if (likely(count < I40E_MAX_BUFFER_TXD))
		return false;

	if (skb_is_gso(skb))
		return __i40e_chk_linearize(skb);

	/* we can support up to 8 data buffers for a single send */
	return count != I40E_MAX_BUFFER_TXD;
}