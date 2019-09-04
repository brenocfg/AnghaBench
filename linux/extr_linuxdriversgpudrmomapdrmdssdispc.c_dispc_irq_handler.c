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
struct dispc_device {int /*<<< orphan*/  user_data; int /*<<< orphan*/  (* user_handler ) (int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  is_enabled; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t dispc_irq_handler(int irq, void *arg)
{
	struct dispc_device *dispc = arg;

	if (!dispc->is_enabled)
		return IRQ_NONE;

	return dispc->user_handler(irq, dispc->user_data);
}