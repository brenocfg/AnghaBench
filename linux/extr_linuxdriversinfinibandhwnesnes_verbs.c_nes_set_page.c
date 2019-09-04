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
struct nes_mr {scalar_t__ npages; scalar_t__ max_pages; int /*<<< orphan*/ * pages; } ;
struct ib_mr {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct nes_mr* to_nesmr (struct ib_mr*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nes_set_page(struct ib_mr *ibmr, u64 addr)
{
	struct nes_mr *nesmr = to_nesmr(ibmr);

	if (unlikely(nesmr->npages == nesmr->max_pages))
		return -ENOMEM;

	nesmr->pages[nesmr->npages++] = cpu_to_le64(addr);

	return 0;
}