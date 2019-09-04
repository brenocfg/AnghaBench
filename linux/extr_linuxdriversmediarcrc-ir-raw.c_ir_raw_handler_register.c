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
struct ir_raw_handler {int /*<<< orphan*/  protocols; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic64_or (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  available_protocols ; 
 int /*<<< orphan*/  ir_raw_handler_list ; 
 int /*<<< orphan*/  ir_raw_handler_lock ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ir_raw_handler_register(struct ir_raw_handler *ir_raw_handler)
{
	mutex_lock(&ir_raw_handler_lock);
	list_add_tail(&ir_raw_handler->list, &ir_raw_handler_list);
	atomic64_or(ir_raw_handler->protocols, &available_protocols);
	mutex_unlock(&ir_raw_handler_lock);

	return 0;
}