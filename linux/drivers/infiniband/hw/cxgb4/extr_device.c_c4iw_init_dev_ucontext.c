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
struct c4iw_rdev {int dummy; } ;
struct c4iw_dev_ucontext {int /*<<< orphan*/  lock; int /*<<< orphan*/  cqids; int /*<<< orphan*/  qpids; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

void c4iw_init_dev_ucontext(struct c4iw_rdev *rdev,
			    struct c4iw_dev_ucontext *uctx)
{
	INIT_LIST_HEAD(&uctx->qpids);
	INIT_LIST_HEAD(&uctx->cqids);
	mutex_init(&uctx->lock);
}