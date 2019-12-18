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
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_2__ {int /*<<< orphan*/  user_data; int /*<<< orphan*/  (* user_handler ) (int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  is_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_NONE ; 
 TYPE_1__ dispc ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t dispc_irq_handler(int irq, void *arg)
{
	if (!dispc.is_enabled)
		return IRQ_NONE;

	return dispc.user_handler(irq, dispc.user_data);
}