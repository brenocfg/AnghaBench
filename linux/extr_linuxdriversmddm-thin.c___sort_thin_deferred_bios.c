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
struct thin_c {struct bio_list deferred_bio_list; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __extract_sorted_bios (struct thin_c*) ; 
 int /*<<< orphan*/  __thin_bio_rb_add (struct thin_c*,struct bio*) ; 
 int /*<<< orphan*/  bio_list_init (struct bio_list*) ; 
 int /*<<< orphan*/  bio_list_merge (struct bio_list*,struct bio_list*) ; 
 struct bio* bio_list_pop (struct bio_list*) ; 

__attribute__((used)) static void __sort_thin_deferred_bios(struct thin_c *tc)
{
	struct bio *bio;
	struct bio_list bios;

	bio_list_init(&bios);
	bio_list_merge(&bios, &tc->deferred_bio_list);
	bio_list_init(&tc->deferred_bio_list);

	/* Sort deferred_bio_list using rb-tree */
	while ((bio = bio_list_pop(&bios)))
		__thin_bio_rb_add(tc, bio);

	/*
	 * Transfer the sorted bios in sort_bio_list back to
	 * deferred_bio_list to allow lockless submission of
	 * all bios.
	 */
	__extract_sorted_bios(tc);
}