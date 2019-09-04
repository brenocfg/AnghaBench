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
struct kvmppc_slb {int /*<<< orphan*/  base_page_size; } ;

/* Variables and functions */
 int mmu_pagesize (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvmppc_mmu_book3s_64_get_pagesize(struct kvmppc_slb *slbe)
{
	return mmu_pagesize(slbe->base_page_size);
}