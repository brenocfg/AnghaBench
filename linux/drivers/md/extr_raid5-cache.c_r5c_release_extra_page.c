#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stripe_head {int disks; TYPE_2__* dev; struct r5conf* raid_conf; } ;
struct r5conf {TYPE_3__* mddev; int /*<<< orphan*/  cache_state; TYPE_1__* disks; } ;
struct page {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  thread; } ;
struct TYPE_5__ {int /*<<< orphan*/  flags; struct page* page; struct page* orig_page; } ;
struct TYPE_4__ {struct page* extra_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  R5C_EXTRA_PAGE_IN_USE ; 
 int /*<<< orphan*/  R5_OrigPageUPTDODATE ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_wakeup_thread (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

void r5c_release_extra_page(struct stripe_head *sh)
{
	struct r5conf *conf = sh->raid_conf;
	int i;
	bool using_disk_info_extra_page;

	using_disk_info_extra_page =
		sh->dev[0].orig_page == conf->disks[0].extra_page;

	for (i = sh->disks; i--; )
		if (sh->dev[i].page != sh->dev[i].orig_page) {
			struct page *p = sh->dev[i].orig_page;

			sh->dev[i].orig_page = sh->dev[i].page;
			clear_bit(R5_OrigPageUPTDODATE, &sh->dev[i].flags);

			if (!using_disk_info_extra_page)
				put_page(p);
		}

	if (using_disk_info_extra_page) {
		clear_bit(R5C_EXTRA_PAGE_IN_USE, &conf->cache_state);
		md_wakeup_thread(conf->mddev->thread);
	}
}