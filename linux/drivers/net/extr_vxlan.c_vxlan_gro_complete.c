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
struct vxlanhdr {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int eth_gro_complete (struct sk_buff*,int) ; 

__attribute__((used)) static int vxlan_gro_complete(struct sock *sk, struct sk_buff *skb, int nhoff)
{
	/* Sets 'skb->inner_mac_header' since we are always called with
	 * 'skb->encapsulation' set.
	 */
	return eth_gro_complete(skb, nhoff + sizeof(struct vxlanhdr));
}