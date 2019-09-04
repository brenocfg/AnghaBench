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
struct drbd_thread {int (* function ) (struct drbd_thread*) ;char const* name; int /*<<< orphan*/ * connection; struct drbd_resource* resource; int /*<<< orphan*/  t_state; int /*<<< orphan*/ * task; int /*<<< orphan*/  t_lock; } ;
struct drbd_resource {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NONE ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void drbd_thread_init(struct drbd_resource *resource, struct drbd_thread *thi,
			     int (*func) (struct drbd_thread *), const char *name)
{
	spin_lock_init(&thi->t_lock);
	thi->task    = NULL;
	thi->t_state = NONE;
	thi->function = func;
	thi->resource = resource;
	thi->connection = NULL;
	thi->name = name;
}