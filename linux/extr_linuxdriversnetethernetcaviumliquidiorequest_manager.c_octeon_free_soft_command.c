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
struct octeon_soft_command {int /*<<< orphan*/  node; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  alloc_buf_count; int /*<<< orphan*/  head; } ;
struct octeon_device {TYPE_1__ sc_buf_pool; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

void octeon_free_soft_command(struct octeon_device *oct,
			      struct octeon_soft_command *sc)
{
	spin_lock_bh(&oct->sc_buf_pool.lock);

	list_add_tail(&sc->node, &oct->sc_buf_pool.head);

	atomic_dec(&oct->sc_buf_pool.alloc_buf_count);

	spin_unlock_bh(&oct->sc_buf_pool.lock);
}