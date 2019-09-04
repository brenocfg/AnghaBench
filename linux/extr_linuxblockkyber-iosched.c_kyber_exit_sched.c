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
struct kyber_queue_data {int /*<<< orphan*/  cb; int /*<<< orphan*/ * domain_tokens; struct request_queue* q; } ;
struct elevator_queue {struct kyber_queue_data* elevator_data; } ;

/* Variables and functions */
 int KYBER_NUM_DOMAINS ; 
 int /*<<< orphan*/  blk_stat_free_callback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_stat_remove_callback (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct kyber_queue_data*) ; 
 int /*<<< orphan*/  sbitmap_queue_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void kyber_exit_sched(struct elevator_queue *e)
{
	struct kyber_queue_data *kqd = e->elevator_data;
	struct request_queue *q = kqd->q;
	int i;

	blk_stat_remove_callback(q, kqd->cb);

	for (i = 0; i < KYBER_NUM_DOMAINS; i++)
		sbitmap_queue_free(&kqd->domain_tokens[i]);
	blk_stat_free_callback(kqd->cb);
	kfree(kqd);
}