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
struct octeon_skb_page_info {scalar_t__ page_offset; int /*<<< orphan*/ * page; scalar_t__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
recv_buffer_destroy(void *buffer, struct octeon_skb_page_info *pg_info)
{
	struct sk_buff *skb = (struct sk_buff *)buffer;

	put_page(pg_info->page);
	pg_info->dma = 0;
	pg_info->page = NULL;
	pg_info->page_offset = 0;

	if (skb)
		dev_kfree_skb_any(skb);
}