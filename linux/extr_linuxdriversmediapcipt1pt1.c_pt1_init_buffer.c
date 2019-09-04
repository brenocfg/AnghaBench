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
typedef  int /*<<< orphan*/  u32 ;
struct pt1_buffer_page {scalar_t__* upackets; } ;
struct pt1_buffer {int /*<<< orphan*/  addr; struct pt1_buffer_page* page; } ;
struct pt1 {int dummy; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int ENOMEM ; 
 int PT1_NR_UPACKETS ; 
 struct pt1_buffer_page* pt1_alloc_page (struct pt1*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pt1_init_buffer(struct pt1 *pt1, struct pt1_buffer *buf,  u32 *pfnp)
{
	struct pt1_buffer_page *page;
	dma_addr_t addr;

	page = pt1_alloc_page(pt1, &addr, pfnp);
	if (page == NULL)
		return -ENOMEM;

	page->upackets[PT1_NR_UPACKETS - 1] = 0;

	buf->page = page;
	buf->addr = addr;
	return 0;
}