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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 int RESYNC_PAGES ; 
 int /*<<< orphan*/  alloc_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int resync_alloc_pages(struct resync_pages *rp,
				     gfp_t gfp_flags)
{
	int i;

	for (i = 0; i < RESYNC_PAGES; i++) {
		rp->pages[i] = alloc_page(gfp_flags);
		if (!rp->pages[i])
			goto out_free;
	}

	return 0;

out_free:
	while (--i >= 0)
		put_page(rp->pages[i]);
	return -ENOMEM;
}