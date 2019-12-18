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
struct blk_plug {int dummy; } ;
struct bio_list {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 struct bio* bio_list_pop (struct bio_list*) ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 int /*<<< orphan*/  generic_make_request (struct bio*) ; 

__attribute__((used)) static void submit_bios(struct bio_list *bios)
{
	struct bio *bio;
	struct blk_plug plug;

	blk_start_plug(&plug);

	while ((bio = bio_list_pop(bios)))
		generic_make_request(bio);

	blk_finish_plug(&plug);
}