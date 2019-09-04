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
struct r10bio {int /*<<< orphan*/  read_slot; } ;
struct bio {struct r10bio* bi_private; } ;

/* Variables and functions */
 int /*<<< orphan*/  __end_sync_read (struct r10bio*,struct bio*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void end_reshape_read(struct bio *bio)
{
	/* reshape read bio isn't allocated from r10buf_pool */
	struct r10bio *r10_bio = bio->bi_private;

	__end_sync_read(r10_bio, bio, r10_bio->read_slot);
}