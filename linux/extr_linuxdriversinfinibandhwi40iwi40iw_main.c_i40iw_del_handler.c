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
struct i40iw_handler {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  i40iw_handler_lock ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int i40iw_del_handler(struct i40iw_handler *hdl)
{
	unsigned long flags;

	spin_lock_irqsave(&i40iw_handler_lock, flags);
	list_del(&hdl->list);
	spin_unlock_irqrestore(&i40iw_handler_lock, flags);
	return 0;
}