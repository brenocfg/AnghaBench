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
struct st_buffer {int frp_segs; int reserved_page_order; int cleared; int /*<<< orphan*/ * reserved_pages; } ;

/* Variables and functions */
 int PAGE_SIZE ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  page_address (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clear_buffer(struct st_buffer * st_bp)
{
	int i;

	for (i=0; i < st_bp->frp_segs; i++)
		memset(page_address(st_bp->reserved_pages[i]), 0,
		       PAGE_SIZE << st_bp->reserved_page_order);
	st_bp->cleared = 1;
}