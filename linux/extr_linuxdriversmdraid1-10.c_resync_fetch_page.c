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
struct resync_pages {struct page** pages; } ;
struct page {int dummy; } ;

/* Variables and functions */
 unsigned int RESYNC_PAGES ; 
 scalar_t__ WARN_ON_ONCE (int) ; 

__attribute__((used)) static inline struct page *resync_fetch_page(struct resync_pages *rp,
					     unsigned idx)
{
	if (WARN_ON_ONCE(idx >= RESYNC_PAGES))
		return NULL;
	return rp->pages[idx];
}