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
struct mapped_device {int /*<<< orphan*/  work; int /*<<< orphan*/  wq; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMF_BLOCK_IO_FOR_SUSPEND ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 

__attribute__((used)) static void dm_queue_flush(struct mapped_device *md)
{
	clear_bit(DMF_BLOCK_IO_FOR_SUSPEND, &md->flags);
	smp_mb__after_atomic();
	queue_work(md->wq, &md->work);
}