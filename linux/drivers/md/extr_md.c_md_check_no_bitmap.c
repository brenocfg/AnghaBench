#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  offset; int /*<<< orphan*/  file; } ;
struct mddev {TYPE_2__* pers; TYPE_1__ bitmap_info; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  mdname (struct mddev*) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int md_check_no_bitmap(struct mddev *mddev)
{
	if (!mddev->bitmap_info.file && !mddev->bitmap_info.offset)
		return 0;
	pr_warn("%s: bitmaps are not supported for %s\n",
		mdname(mddev), mddev->pers->name);
	return 1;
}