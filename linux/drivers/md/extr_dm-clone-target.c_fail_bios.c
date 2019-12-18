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
struct bio_list {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_status; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int /*<<< orphan*/  bio_endio (struct bio*) ; 
 struct bio* bio_list_pop (struct bio_list*) ; 

__attribute__((used)) static void fail_bios(struct bio_list *bios, blk_status_t status)
{
	struct bio *bio;

	while ((bio = bio_list_pop(bios))) {
		bio->bi_status = status;
		bio_endio(bio);
	}
}