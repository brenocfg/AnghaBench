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
struct r1bio {TYPE_1__* mddev; int /*<<< orphan*/  state; int /*<<< orphan*/  sectors; int /*<<< orphan*/  sector; int /*<<< orphan*/ * behind_master_bio; } ;
struct TYPE_2__ {int /*<<< orphan*/  bitmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  R1BIO_BehindIO ; 
 int /*<<< orphan*/  R1BIO_Degraded ; 
 int /*<<< orphan*/  bio_free_pages (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  md_bitmap_endwrite (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  md_write_end (TYPE_1__*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void close_write(struct r1bio *r1_bio)
{
	/* it really is the end of this request */
	if (test_bit(R1BIO_BehindIO, &r1_bio->state)) {
		bio_free_pages(r1_bio->behind_master_bio);
		bio_put(r1_bio->behind_master_bio);
		r1_bio->behind_master_bio = NULL;
	}
	/* clear the bitmap if all writes complete successfully */
	md_bitmap_endwrite(r1_bio->mddev->bitmap, r1_bio->sector,
			   r1_bio->sectors,
			   !test_bit(R1BIO_Degraded, &r1_bio->state),
			   test_bit(R1BIO_BehindIO, &r1_bio->state));
	md_write_end(r1_bio->mddev);
}