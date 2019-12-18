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
typedef  int /*<<< orphan*/  u64 ;
struct pvrdma_page_dir {int /*<<< orphan*/ ** tables; } ;

/* Variables and functions */
 size_t PVRDMA_PAGE_DIR_TABLE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u64 *pvrdma_page_dir_table(struct pvrdma_page_dir *pdir, u64 idx)
{
	return pdir->tables[PVRDMA_PAGE_DIR_TABLE(idx)];
}