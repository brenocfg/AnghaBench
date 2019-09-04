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
struct rsxx_cardinfo {TYPE_1__* gendisk; int /*<<< orphan*/  queue; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  part0; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_op (struct bio*) ; 
 int /*<<< orphan*/  bio_sectors (struct bio*) ; 
 int /*<<< orphan*/  generic_start_io_acct (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void disk_stats_start(struct rsxx_cardinfo *card, struct bio *bio)
{
	generic_start_io_acct(card->queue, bio_op(bio), bio_sectors(bio),
			     &card->gendisk->part0);
}