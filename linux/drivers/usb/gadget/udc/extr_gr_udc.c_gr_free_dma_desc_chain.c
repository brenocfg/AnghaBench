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
struct gr_udc {int dummy; } ;
struct gr_request {struct gr_dma_desc* last_desc; int /*<<< orphan*/ * curr_desc; struct gr_dma_desc* first_desc; } ;
struct gr_dma_desc {struct gr_dma_desc* next_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  gr_free_dma_desc (struct gr_udc*,struct gr_dma_desc*) ; 

__attribute__((used)) static void gr_free_dma_desc_chain(struct gr_udc *dev, struct gr_request *req)
{
	struct gr_dma_desc *desc;
	struct gr_dma_desc *next;

	next = req->first_desc;
	if (!next)
		return;

	do {
		desc = next;
		next = desc->next_desc;
		gr_free_dma_desc(dev, desc);
	} while (desc != req->last_desc);

	req->first_desc = NULL;
	req->curr_desc = NULL;
	req->last_desc = NULL;
}