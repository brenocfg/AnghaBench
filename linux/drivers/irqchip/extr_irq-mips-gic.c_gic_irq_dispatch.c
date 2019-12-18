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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  gic_handle_local_int (int) ; 
 int /*<<< orphan*/  gic_handle_shared_int (int) ; 

__attribute__((used)) static void gic_irq_dispatch(struct irq_desc *desc)
{
	gic_handle_local_int(true);
	gic_handle_shared_int(true);
}