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
struct driver_data {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  mtip_handle_irq (struct driver_data*) ; 

__attribute__((used)) static irqreturn_t mtip_irq_handler(int irq, void *instance)
{
	struct driver_data *dd = instance;

	return mtip_handle_irq(dd);
}