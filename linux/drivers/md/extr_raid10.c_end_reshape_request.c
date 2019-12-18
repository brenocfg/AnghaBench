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
struct r10bio {int /*<<< orphan*/  master_bio; int /*<<< orphan*/  sectors; int /*<<< orphan*/  mddev; int /*<<< orphan*/  remaining; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bio_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  md_done_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_buf (struct r10bio*) ; 

__attribute__((used)) static void end_reshape_request(struct r10bio *r10_bio)
{
	if (!atomic_dec_and_test(&r10_bio->remaining))
		return;
	md_done_sync(r10_bio->mddev, r10_bio->sectors, 1);
	bio_put(r10_bio->master_bio);
	put_buf(r10_bio);
}