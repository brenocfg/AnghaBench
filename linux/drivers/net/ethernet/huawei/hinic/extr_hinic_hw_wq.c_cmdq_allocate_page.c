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
struct hinic_cmdq_pages {int /*<<< orphan*/  shadow_page_vaddr; int /*<<< orphan*/  page_paddr; int /*<<< orphan*/  page_vaddr; int /*<<< orphan*/  hwif; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMDQ_PAGE_SIZE ; 
 int queue_alloc_page (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cmdq_allocate_page(struct hinic_cmdq_pages *cmdq_pages)
{
	return queue_alloc_page(cmdq_pages->hwif, &cmdq_pages->page_vaddr,
				&cmdq_pages->page_paddr,
				&cmdq_pages->shadow_page_vaddr,
				CMDQ_PAGE_SIZE);
}