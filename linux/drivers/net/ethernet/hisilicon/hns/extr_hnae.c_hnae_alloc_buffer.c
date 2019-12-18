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
struct page {int dummy; } ;
struct hnae_ring {int dummy; } ;
struct hnae_desc_cb {int /*<<< orphan*/  type; int /*<<< orphan*/  length; int /*<<< orphan*/  buf; scalar_t__ reuse_flag; scalar_t__ page_offset; struct page* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DESC_TYPE_PAGE ; 
 int ENOMEM ; 
 struct page* dev_alloc_pages (unsigned int) ; 
 unsigned int hnae_page_order (struct hnae_ring*) ; 
 int /*<<< orphan*/  hnae_page_size (struct hnae_ring*) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 

__attribute__((used)) static int hnae_alloc_buffer(struct hnae_ring *ring, struct hnae_desc_cb *cb)
{
	unsigned int order = hnae_page_order(ring);
	struct page *p = dev_alloc_pages(order);

	if (!p)
		return -ENOMEM;

	cb->priv = p;
	cb->page_offset = 0;
	cb->reuse_flag = 0;
	cb->buf  = page_address(p);
	cb->length = hnae_page_size(ring);
	cb->type = DESC_TYPE_PAGE;

	return 0;
}