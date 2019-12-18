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
struct vsp1_pipeline {int /*<<< orphan*/  state; int /*<<< orphan*/  entities; int /*<<< orphan*/  kref; int /*<<< orphan*/  wq; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VSP1_PIPELINE_STOPPED ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void vsp1_pipeline_init(struct vsp1_pipeline *pipe)
{
	mutex_init(&pipe->lock);
	spin_lock_init(&pipe->irqlock);
	init_waitqueue_head(&pipe->wq);
	kref_init(&pipe->kref);

	INIT_LIST_HEAD(&pipe->entities);
	pipe->state = VSP1_PIPELINE_STOPPED;
}