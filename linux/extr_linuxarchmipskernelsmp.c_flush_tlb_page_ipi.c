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
struct flush_tlb_data {int /*<<< orphan*/  addr1; int /*<<< orphan*/  vma; } ;

/* Variables and functions */
 int /*<<< orphan*/  local_flush_tlb_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flush_tlb_page_ipi(void *info)
{
	struct flush_tlb_data *fd = info;

	local_flush_tlb_page(fd->vma, fd->addr1);
}