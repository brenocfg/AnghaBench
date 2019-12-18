#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stripe_head {int disks; struct r5dev* dev; struct r5conf* raid_conf; } ;
struct r5dev {scalar_t__ orig_page; scalar_t__ page; } ;
struct r5conf {TYPE_1__* disks; } ;
struct TYPE_2__ {scalar_t__ extra_page; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_page (scalar_t__) ; 

void r5c_use_extra_page(struct stripe_head *sh)
{
	struct r5conf *conf = sh->raid_conf;
	int i;
	struct r5dev *dev;

	for (i = sh->disks; i--; ) {
		dev = &sh->dev[i];
		if (dev->orig_page != dev->page)
			put_page(dev->orig_page);
		dev->orig_page = conf->disks[i].extra_page;
	}
}