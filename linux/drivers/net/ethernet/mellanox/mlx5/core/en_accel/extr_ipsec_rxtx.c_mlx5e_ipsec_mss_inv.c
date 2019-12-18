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
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_2__ {size_t gso_size; } ;

/* Variables and functions */
 int /*<<< orphan*/ * mlx5e_ipsec_inverse_table ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static inline __be16 mlx5e_ipsec_mss_inv(struct sk_buff *skb)
{
	return mlx5e_ipsec_inverse_table[skb_shinfo(skb)->gso_size];
}