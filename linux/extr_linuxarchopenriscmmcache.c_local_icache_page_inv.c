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
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SPR_ICBIR ; 
 int /*<<< orphan*/  cache_loop (struct page*,int /*<<< orphan*/ ) ; 

void local_icache_page_inv(struct page *page)
{
	cache_loop(page, SPR_ICBIR);
}