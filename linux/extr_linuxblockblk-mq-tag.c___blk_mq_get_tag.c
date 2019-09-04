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
struct sbitmap_queue {int dummy; } ;
struct blk_mq_alloc_data {int flags; scalar_t__ shallow_depth; int /*<<< orphan*/  hctx; } ;

/* Variables and functions */
 int BLK_MQ_REQ_INTERNAL ; 
 int __sbitmap_queue_get (struct sbitmap_queue*) ; 
 int __sbitmap_queue_get_shallow (struct sbitmap_queue*,scalar_t__) ; 
 int /*<<< orphan*/  hctx_may_queue (int /*<<< orphan*/ ,struct sbitmap_queue*) ; 

__attribute__((used)) static int __blk_mq_get_tag(struct blk_mq_alloc_data *data,
			    struct sbitmap_queue *bt)
{
	if (!(data->flags & BLK_MQ_REQ_INTERNAL) &&
	    !hctx_may_queue(data->hctx, bt))
		return -1;
	if (data->shallow_depth)
		return __sbitmap_queue_get_shallow(bt, data->shallow_depth);
	else
		return __sbitmap_queue_get(bt);
}