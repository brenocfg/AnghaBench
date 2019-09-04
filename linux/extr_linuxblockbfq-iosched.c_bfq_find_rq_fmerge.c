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
struct request_queue {int dummy; } ;
struct request {int dummy; } ;
struct bio {int dummy; } ;
struct bfq_queue {int /*<<< orphan*/  sort_list; } ;
struct bfq_data {struct bfq_queue* bio_bfqq; } ;

/* Variables and functions */
 int /*<<< orphan*/  bio_end_sector (struct bio*) ; 
 struct request* elv_rb_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct request *bfq_find_rq_fmerge(struct bfq_data *bfqd,
					  struct bio *bio,
					  struct request_queue *q)
{
	struct bfq_queue *bfqq = bfqd->bio_bfqq;


	if (bfqq)
		return elv_rb_find(&bfqq->sort_list, bio_end_sector(bio));

	return NULL;
}