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
typedef  scalar_t__ u16 ;
struct sk_buff {int /*<<< orphan*/  truesize; int /*<<< orphan*/  data_len; int /*<<< orphan*/  len; } ;
struct e1000_buffer {int /*<<< orphan*/ * page; } ;

/* Variables and functions */
 scalar_t__ PAGE_SIZE ; 

__attribute__((used)) static void e1000_consume_page(struct e1000_buffer *bi, struct sk_buff *skb,
			       u16 length)
{
	bi->page = NULL;
	skb->len += length;
	skb->data_len += length;
	skb->truesize += PAGE_SIZE;
}