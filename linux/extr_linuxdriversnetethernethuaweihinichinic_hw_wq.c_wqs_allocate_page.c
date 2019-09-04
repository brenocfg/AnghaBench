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
struct hinic_wqs {int /*<<< orphan*/ * shadow_page_vaddr; int /*<<< orphan*/ * page_paddr; int /*<<< orphan*/ * page_vaddr; int /*<<< orphan*/  hwif; } ;

/* Variables and functions */
 int /*<<< orphan*/  WQS_PAGE_SIZE ; 
 int queue_alloc_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wqs_allocate_page(struct hinic_wqs *wqs, int page_idx)
{
	return queue_alloc_page(wqs->hwif, &wqs->page_vaddr[page_idx],
				&wqs->page_paddr[page_idx],
				&wqs->shadow_page_vaddr[page_idx],
				WQS_PAGE_SIZE);
}