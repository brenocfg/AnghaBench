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
struct txfcb {int /*<<< orphan*/  vlctl; int /*<<< orphan*/  flags; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TXFCB_VLN ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_vlan_tag_get (struct sk_buff*) ; 

__attribute__((used)) static inline void gfar_tx_vlan(struct sk_buff *skb, struct txfcb *fcb)
{
	fcb->flags |= TXFCB_VLN;
	fcb->vlctl = cpu_to_be16(skb_vlan_tag_get(skb));
}