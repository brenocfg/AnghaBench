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
struct resync_pages {int /*<<< orphan*/ * pages; } ;

/* Variables and functions */
 int RESYNC_PAGES ; 
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void resync_get_all_pages(struct resync_pages *rp)
{
	int i;

	for (i = 0; i < RESYNC_PAGES; i++)
		get_page(rp->pages[i]);
}