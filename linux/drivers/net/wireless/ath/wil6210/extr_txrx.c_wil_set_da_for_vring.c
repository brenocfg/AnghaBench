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
typedef  int /*<<< orphan*/  u8 ;
struct wil6210_priv {int** ring2cid_tid; TYPE_1__* sta; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * wil_skb_get_da (struct sk_buff*) ; 

__attribute__((used)) static void wil_set_da_for_vring(struct wil6210_priv *wil,
				 struct sk_buff *skb, int vring_index)
{
	u8 *da = wil_skb_get_da(skb);
	int cid = wil->ring2cid_tid[vring_index][0];

	ether_addr_copy(da, wil->sta[cid].addr);
}