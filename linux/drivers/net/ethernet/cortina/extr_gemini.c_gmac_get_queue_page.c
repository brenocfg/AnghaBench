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
struct gmac_queue_page {int mapping; } ;
struct gemini_ethernet_port {int dummy; } ;
struct gemini_ethernet {int num_freeq_pages; struct gmac_queue_page* freeq_pages; int /*<<< orphan*/  dev; } ;
typedef  int dma_addr_t ;

/* Variables and functions */
 int PAGE_MASK ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct gmac_queue_page *
gmac_get_queue_page(struct gemini_ethernet *geth,
		    struct gemini_ethernet_port *port,
		    dma_addr_t addr)
{
	struct gmac_queue_page *gpage;
	dma_addr_t mapping;
	int i;

	/* Only look for even pages */
	mapping = addr & PAGE_MASK;

	if (!geth->freeq_pages) {
		dev_err(geth->dev, "try to get page with no page list\n");
		return NULL;
	}

	/* Look up a ring buffer page from virtual mapping */
	for (i = 0; i < geth->num_freeq_pages; i++) {
		gpage = &geth->freeq_pages[i];
		if (gpage->mapping == mapping)
			return gpage;
	}

	return NULL;
}