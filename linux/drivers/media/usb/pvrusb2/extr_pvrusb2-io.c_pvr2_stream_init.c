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
struct pvr2_stream {int /*<<< orphan*/  idle_list; int /*<<< orphan*/  ready_list; int /*<<< orphan*/  queued_list; int /*<<< orphan*/  mutex; int /*<<< orphan*/  list_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pvr2_stream_init(struct pvr2_stream *sp)
{
	spin_lock_init(&sp->list_lock);
	mutex_init(&sp->mutex);
	INIT_LIST_HEAD(&sp->queued_list);
	INIT_LIST_HEAD(&sp->ready_list);
	INIT_LIST_HEAD(&sp->idle_list);
}