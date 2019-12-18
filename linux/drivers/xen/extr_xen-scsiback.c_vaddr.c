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
struct vscsibk_pend {int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 unsigned long vaddr_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long vaddr(struct vscsibk_pend *req, int seg)
{
	return vaddr_page(req->pages[seg]);
}