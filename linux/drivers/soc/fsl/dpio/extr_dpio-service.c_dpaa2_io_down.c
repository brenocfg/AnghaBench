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
struct TYPE_2__ {size_t cpu; } ;
struct dpaa2_io {int /*<<< orphan*/  node; TYPE_1__ dpio_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/ ** dpio_by_cpu ; 
 int /*<<< orphan*/  dpio_list_lock ; 
 int /*<<< orphan*/  kfree (struct dpaa2_io*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void dpaa2_io_down(struct dpaa2_io *d)
{
	spin_lock(&dpio_list_lock);
	dpio_by_cpu[d->dpio_desc.cpu] = NULL;
	list_del(&d->node);
	spin_unlock(&dpio_list_lock);

	kfree(d);
}