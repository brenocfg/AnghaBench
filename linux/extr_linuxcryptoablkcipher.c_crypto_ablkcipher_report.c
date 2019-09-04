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
struct crypto_alg {int dummy; } ;

/* Variables and functions */
 int ENOSYS ; 

__attribute__((used)) static int crypto_ablkcipher_report(struct sk_buff *skb, struct crypto_alg *alg)
{
	return -ENOSYS;
}