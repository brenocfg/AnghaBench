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
struct nullb_page {int dummy; } ;
struct nullb {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 struct nullb_page* __null_lookup_page (struct nullb*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static struct nullb_page *null_lookup_page(struct nullb *nullb,
	sector_t sector, bool for_write, bool ignore_cache)
{
	struct nullb_page *page = NULL;

	if (!ignore_cache)
		page = __null_lookup_page(nullb, sector, for_write, true);
	if (page)
		return page;
	return __null_lookup_page(nullb, sector, for_write, false);
}