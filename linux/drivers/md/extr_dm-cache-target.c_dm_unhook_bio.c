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
struct dm_hook_info {int /*<<< orphan*/  bi_end_io; } ;
struct bio {int /*<<< orphan*/  bi_end_io; } ;

/* Variables and functions */

__attribute__((used)) static void dm_unhook_bio(struct dm_hook_info *h, struct bio *bio)
{
	bio->bi_end_io = h->bi_end_io;
}