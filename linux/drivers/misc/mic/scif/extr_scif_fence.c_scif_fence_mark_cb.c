#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  fence_refcount; int /*<<< orphan*/  markwq; } ;
struct scif_endpt {TYPE_1__ rma_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void scif_fence_mark_cb(void *arg)
{
	struct scif_endpt *ep = (struct scif_endpt *)arg;

	wake_up_interruptible(&ep->rma_info.markwq);
	atomic_dec(&ep->rma_info.fence_refcount);
}