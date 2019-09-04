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
struct brd_device {int /*<<< orphan*/  brd_disk; int /*<<< orphan*/  brd_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  brd_free (struct brd_device*) ; 
 int /*<<< orphan*/  del_gendisk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void brd_del_one(struct brd_device *brd)
{
	list_del(&brd->brd_list);
	del_gendisk(brd->brd_disk);
	brd_free(brd);
}