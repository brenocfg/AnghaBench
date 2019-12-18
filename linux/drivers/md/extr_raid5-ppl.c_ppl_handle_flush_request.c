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
struct r5l_log {int dummy; } ;
struct TYPE_2__ {scalar_t__ bi_size; } ;
struct bio {int /*<<< orphan*/  bi_opf; TYPE_1__ bi_iter; } ;

/* Variables and functions */
 int EAGAIN ; 
 int /*<<< orphan*/  REQ_PREFLUSH ; 
 int /*<<< orphan*/  bio_endio (struct bio*) ; 

int ppl_handle_flush_request(struct r5l_log *log, struct bio *bio)
{
	if (bio->bi_iter.bi_size == 0) {
		bio_endio(bio);
		return 0;
	}
	bio->bi_opf &= ~REQ_PREFLUSH;
	return -EAGAIN;
}