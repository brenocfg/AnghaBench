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
struct rvu {int /*<<< orphan*/  dev; } ;
struct admin_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  res; int /*<<< orphan*/  inst; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  devm_kfree (int /*<<< orphan*/ ,struct admin_queue*) ; 
 struct admin_queue* devm_kzalloc (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int qmem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  rvu_aq_free (struct rvu*,struct admin_queue*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int rvu_aq_alloc(struct rvu *rvu, struct admin_queue **ad_queue,
		 int qsize, int inst_size, int res_size)
{
	struct admin_queue *aq;
	int err;

	*ad_queue = devm_kzalloc(rvu->dev, sizeof(*aq), GFP_KERNEL);
	if (!*ad_queue)
		return -ENOMEM;
	aq = *ad_queue;

	/* Alloc memory for instructions i.e AQ */
	err = qmem_alloc(rvu->dev, &aq->inst, qsize, inst_size);
	if (err) {
		devm_kfree(rvu->dev, aq);
		return err;
	}

	/* Alloc memory for results */
	err = qmem_alloc(rvu->dev, &aq->res, qsize, res_size);
	if (err) {
		rvu_aq_free(rvu, aq);
		return err;
	}

	spin_lock_init(&aq->lock);
	return 0;
}