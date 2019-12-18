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
struct scif_window {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  rma_lock; int /*<<< orphan*/  reg_list; } ;
struct scif_endpt {TYPE_1__ rma_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scif_insert_window (struct scif_window*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
scif_insert_local_window(struct scif_window *window, struct scif_endpt *ep)
{
	mutex_lock(&ep->rma_info.rma_lock);
	scif_insert_window(window, &ep->rma_info.reg_list);
	mutex_unlock(&ep->rma_info.rma_lock);
}