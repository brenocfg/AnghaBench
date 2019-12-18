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
struct tty_struct {struct ehv_bc_data* driver_data; } ;
struct ehv_bc_data {int /*<<< orphan*/  lock; int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUF_SIZE ; 
 int CIRC_SPACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ehv_bc_tty_write_room(struct tty_struct *ttys)
{
	struct ehv_bc_data *bc = ttys->driver_data;
	unsigned long flags;
	int count;

	spin_lock_irqsave(&bc->lock, flags);
	count = CIRC_SPACE(bc->head, bc->tail, BUF_SIZE);
	spin_unlock_irqrestore(&bc->lock, flags);

	return count;
}