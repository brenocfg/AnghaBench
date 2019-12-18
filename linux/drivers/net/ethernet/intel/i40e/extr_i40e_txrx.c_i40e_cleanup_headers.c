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
typedef  union i40e_rx_desc {int dummy; } i40e_rx_desc ;
struct sk_buff {int dummy; } ;
struct i40e_ring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  I40E_RXD_QW1_ERROR_SHIFT ; 
 scalar_t__ IS_ERR (struct sk_buff*) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ eth_skb_pad (struct sk_buff*) ; 
 int /*<<< orphan*/  i40e_test_staterr (union i40e_rx_desc*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool i40e_cleanup_headers(struct i40e_ring *rx_ring, struct sk_buff *skb,
				 union i40e_rx_desc *rx_desc)

{
	/* XDP packets use error pointer so abort at this point */
	if (IS_ERR(skb))
		return true;

	/* ERR_MASK will only have valid bits if EOP set, and
	 * what we are doing here is actually checking
	 * I40E_RX_DESC_ERROR_RXE_SHIFT, since it is the zeroth bit in
	 * the error field
	 */
	if (unlikely(i40e_test_staterr(rx_desc,
				       BIT(I40E_RXD_QW1_ERROR_SHIFT)))) {
		dev_kfree_skb_any(skb);
		return true;
	}

	/* if eth_skb_pad returns an error the skb was freed */
	if (eth_skb_pad(skb))
		return true;

	return false;
}