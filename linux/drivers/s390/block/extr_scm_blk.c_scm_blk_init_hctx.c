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
struct scm_queue {int /*<<< orphan*/  lock; } ;
struct blk_mq_hw_ctx {struct scm_queue* driver_data; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct scm_queue* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int scm_blk_init_hctx(struct blk_mq_hw_ctx *hctx, void *data,
			     unsigned int idx)
{
	struct scm_queue *qd = kzalloc(sizeof(*qd), GFP_KERNEL);

	if (!qd)
		return -ENOMEM;

	spin_lock_init(&qd->lock);
	hctx->driver_data = qd;

	return 0;
}