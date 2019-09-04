#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct udphdr {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int gso_size; } ;
struct TYPE_3__ {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  htons (int) ; 
 TYPE_2__* skb_shinfo (struct sk_buff*) ; 
 TYPE_1__* udp_hdr (struct sk_buff*) ; 

__attribute__((used)) static inline void
mlx5e_udp_gso_handle_tx_skb(struct sk_buff *skb)
{
	int payload_len = skb_shinfo(skb)->gso_size + sizeof(struct udphdr);

	udp_hdr(skb)->len = htons(payload_len);
}