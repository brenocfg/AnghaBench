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
struct btt {int /*<<< orphan*/  btt_queue; int /*<<< orphan*/  btt_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  del_gendisk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_disk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void btt_blk_cleanup(struct btt *btt)
{
	del_gendisk(btt->btt_disk);
	put_disk(btt->btt_disk);
	blk_cleanup_queue(btt->btt_queue);
}