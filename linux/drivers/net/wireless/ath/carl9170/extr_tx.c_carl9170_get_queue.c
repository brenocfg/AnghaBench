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
struct ar9170 {int dummy; } ;

/* Variables and functions */
 unsigned int __carl9170_get_queue (struct ar9170*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_get_queue_mapping (struct sk_buff*) ; 

__attribute__((used)) static inline unsigned int carl9170_get_queue(struct ar9170 *ar,
					      struct sk_buff *skb)
{
	return __carl9170_get_queue(ar, skb_get_queue_mapping(skb));
}