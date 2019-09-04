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
struct TYPE_2__ {unsigned int nr_frags; } ;

/* Variables and functions */
 int sgl_len (unsigned int) ; 
 TYPE_1__* skb_shinfo (struct sk_buff const*) ; 

__attribute__((used)) static int data_sgl_len(const struct sk_buff *skb)
{
	unsigned int cnt;

	cnt = skb_shinfo(skb)->nr_frags;
	return sgl_len(cnt) * 8;
}