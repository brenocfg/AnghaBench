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
struct bio {int /*<<< orphan*/  bi_opf; } ;

/* Variables and functions */
 int /*<<< orphan*/  RQ_CFQG (struct request*) ; 
 int /*<<< orphan*/  cfqg_stats_update_io_merged (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfq_bio_merged(struct request_queue *q, struct request *req,
				struct bio *bio)
{
	cfqg_stats_update_io_merged(RQ_CFQG(req), bio->bi_opf);
}