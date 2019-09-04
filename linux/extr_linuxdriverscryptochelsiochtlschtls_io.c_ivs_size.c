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
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int CIPHER_BLOCK_SIZE ; 
 int nos_ivs (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ set_ivs_imm (struct sock*,struct sk_buff const*) ; 

__attribute__((used)) static int ivs_size(struct sock *sk, const struct sk_buff *skb)
{
	return set_ivs_imm(sk, skb) ? (nos_ivs(sk, skb->len) *
		 CIPHER_BLOCK_SIZE) : 0;
}